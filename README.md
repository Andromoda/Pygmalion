## Pygmalion

[English](README.md) | [Русский](README_RU.md)

`pygmalion` is a standalone `non-root` `android` library needed for theming applications
by creating hooks for `AssetManager` and `Activity`.

Supports `Android 5.0 - Android 15+` devices with `x86`, `x86_64`, `arm32`, and `arm64` architectures.

> [!CAUTION]
> I and the contributors take no responsibility for any problems caused by the using of this library
> in your projects.
> Also this project is in alpha version because **I can't guarantee backward compatibility support with
> future updates**.

## Motivation
Initially this project was my weird idea to customize android apps without `root`, `xposed`, etc. and I didn't plan to 
use native. But in the end it was the only way to hook `AssetManager`. Also I don't want to use any
`ART hooking framework` because they're more unstable than my method.

## Project Description
`pygmlion` needs for cases when you want to add theming support(ex. changing accent colors),
but you have no source code of target app.
To use it, you should know about **complex** and **value-based (primitive)** resources 
(see [App resources overview](https://developer.android.com/guide/topics/resources/providing-resources)),
also you can check [AssetManager](https://cs.android.com/android/platform/superproject/main/+/main:frameworks/base/core/java/android/content/res/AssetManager.java),
[Resources](https://cs.android.com/android/platform/superproject/main/+/main:frameworks/base/core/java/android/content/res/Resources.java),
[TypedValue](https://cs.android.com/android/platform/superproject/main/+/main:frameworks/base/core/java/android/util/TypedValue.java)
and [TypedArray](https://cs.android.com/android/platform/superproject/main/+/main:frameworks/base/core/java/android/content/res/TypedArray.java) sources
**for specific platform**.

## How it works
`pygmalion` works with two layers:
- **Java layer** provides API for making hooks for `AssetManager` and `Activity`
- **Native layer** uses for hooking `AssetManager` native functions related with resources. by re-registring native functions related with resources to
interact with fetched data (attribute ids, resource values, etc.) before it will be returned to call point.

On the **Native layer**, `pygmalion` hooks function that's used to register all `AssetManager` native functions with signature
```
_ZN7android37register_android_content_AssetManagerEP7_JNIEnv
```
Next, target functions finds by hardcoded names and signatures from the dump and replaced to the hook functions that calls
Java implementation functions. This way is more stable than some `ART hooking framework` because there's
used built-in `JNI` API and tested hooking libraries.

> [!NOTE]
> For Android N, `pygmalion` disables `@FastNative` optimizations for `AssetManager` native functions
> that causes crashes.

## TODO
- Add `LayoutInflater` hooks

## Limitations
- You can only hook `AssetManager` and `Activity`.
- In the `AssetManager` hooks you cannot you cannot add/remove attributes

## Sub-projects:
- `demo` is an android application developed as a "gallery" for demonstration.
- `library` is a core implementation of `pygmalion` providing API needed for making hooks.
- `stub` only provided private android APIs that can't be accessed directly.

## Use cases
I don't recommend to use this library in the regular android development. It needs for cases when
you have no source code, for example, android app modifications such as [Revanced's mods](https://revanced.app/),
[VTLIte](https://github.com/vtosters/lite), etc.

## Integration

#### build.gradle:
```groovy
dependencies {
    implementation fileTree(dir: 'libs', include: ['*.jar', '*.aar'])
}
```

#### build.gradle.kts:
```kotlin
dependencies {
    implementation(
        fileTree("libs") {
            include("*.jar", "*.aar")
        }
    )
}
```

## Development

### Initialization
 `pygmalion` provides API for manually control:

```kotlin
/*
* Initialize pygmalion, check if it's initialized
* and enable hooking 
*/
Pygmalion.initialize()
if(Pygmalion.isInitialized()) {
    Pyhmalion.hook()
}
```

```kotlin
//disable hooking
Pygmalion.unhook()
```

### Hooks

#### Add/remove `AssetManager` hooks:

Kotlin:

```kotlin
@JvmField
val exampleHook =
    assetHook {
        onLoadResourceValue { asset ->
            //etc
        }
        onLoadThemeAttrValue { asset ->
            //etc
        }
        onApplyStyle { assets ->
            //etc
        }
        onResolveAttrs { assets ->
            //etc
        }
        onRetrieveAttrs { assets ->
            //etc
        }
    }

fun hook() {
    //add AssetManager hooks
    Pygmalion.registerAssetHooks(exampleHook,/*...*/)
}

fun unhook() {
    //remove specific AssetManager hooks
    Pygmalion.unregisterAssetHooks(exampleHook)
}
```

Java:

```java
public class HooksExample {
    private static IAssetHook hook = new IAssetHook() {
        @Override
        public void onLoadResourceValueHook(int resId, @NotNull TypedValue outValue, boolean resolveAttrs) {
            //etc
        }

        @Override
        public void onLoadThemeAttrValueHook(int resId, @NotNull TypedValue outValue, boolean resolveAttrs) {
            //etc
        }

        @Override
        public void onApplyStyleHook(int defStyleAttr, int defStyleRes, @NotNull int[] inAttrs, @NotNull List<TypedValue> outValues) {
            //etc
        }

        @Override
        public void onResolveAttrsHook(int defStyleAttr, int defStyleRes, @NotNull int[] inValues, @NotNull int[] inAttrs, @NotNull List<TypedValue> outValues) {
            //etc
        }

        @Override
        public void onRetrieveAttrsHook(@NotNull int[] inAttrs, @NotNull List<TypedValue> outValues) {
            //etc
        }
    };

    public static void hook() {
        //adding AssetManager hooks
        Pygmalion.registerAssetHooks(hook,hook);
    }
    
    public static void unhook() {
        //remove specific AssetManager hooks
        Pygmalion.unregisterAssetHooks(hook,hook);
    }
}
```

#### Add/remove `Activity` hooks:

Kotlin:

```kotlin
@JvmField
val exampleHook = activityLifecycleCallbacks {
    onActivityCreated { activity, bundle : Bundle? ->
        //etc
    }
    
    onActivityResumed { activity ->
        //etc
    }
    
    //etc
}

fun hook() {
    //adding Activity hooks
    Pygmalion.registerActivityLifecycleCallbacks(exampleHook,/*...*/)
}

fun unhook() {
    //remove specific Activity hooks
    Pygmalion.unregisterActivityLifecycleCallbacks(exampleHook,/*...*/)
}
```

Java:

```java
public class HooksExample {
    private static IActivityLifecycleCallback hook = new IActivityLifecycleCallback() {
        @Override
        public void onActivityCreated(@NotNull Activity activity, @Nullable Bundle savedInstanceState) {
            //etc
        }

        @Override
        public void onActivityResumed(@NotNull Activity activity) {
            //etc
        }
        
        //etc
    };

    public static void hook() {
        //adding Activity hooks
        Pygmalion.registerActivityLifecycleCallbacks(hook,hook);
    }

    public static void unhook() {
        //remove specific Activity hooks
        Pygmalion.unregisterActivityLifecycleCallbacks(hook,hook);
    }
}
```