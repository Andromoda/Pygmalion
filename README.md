## Pygmalion

[English](README.md) | [Русский](README_RU.md)

`pygmalion` is a `non-root` standalone `android` library needed for theming `android` applications
by creating hooks for `AssetManager` and `Activity`.

Supports `Android 9.0 - Android 15` devices with `x86`, `x86_64`, `arm`, and `arm64` architectures.

## Disclaimer
I and the contributors take no responsibility for, and will not be liable for,
any problems caused by the using of this library in your projects.
Also, this project is in alpha version now because I can't guarantee backward compatibility support with
future updates.

## Project Description
I do this library for my current and future projects. One of the main goals is providing ability to
add flexible and powerful theming support to `android` application modifications for cases when you have no source code

### Goals
1. Optimize work with native hooks
2. Add `LayoutInflater` hooks
3. etc.

### Limitations
1. Now, you can hook only `AssetManager` and `Activity` by default.
2. You can only change providing attributes in the `AssetManager` hooks

### Sub-projects:
1. The `library` project is a core implementation of `pygmalion` providing API needed for development.
2. The `demo` project is an `android` application developed as "gallery" for demonstration.  
3. the `stub` project only provided private `android` `api`s that can't be accessed directly.

## Use cases
I don't recommend to use this library in the regular `android` development. It needs for cases when
you have no source code, for example, android app modifications such as [Revanced's mods](https://revanced.app/),
[VTLIte](https://github.com/vtosters/lite), etc.

## Integration
> Download the latest [Release version](https://github.com/Andromoda/Pygmalion/releases/latest)
> arr and add it to your project dependencies

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
* check if Pygmalion is initialized
* and enable hooking 
*/
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

#### For more details, see `demo` project and `library` sources