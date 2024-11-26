## Pygmalion

[English](README.md) | [Русский](README_RU.md)

`pygmalion` это автономная библиотека для `android`, не требующая root-прав и необходимая для кастомизации UI android-приложений
посредством создания хуков для `AssetManager` и `Activity`.

Поддерживает `Android 9.0 - Android 15` устройства с `x86`, `x86_64`, `arm`, и `arm64` архитектурами.

## Дисклеймер
Я и контрибьютеры не несём и не будем нести отвественности за любой приченённый вред, вызванный
использованием этой библиотеки в ваших проектах. Также этот проект находится в альфа-стадии, поэтому
обратная совметимость с будущими обновлениями не гарантируется. 

## Описание проекта
Я делаю эту библиотеку для своих текущих и будущих проектов. Одна из основных целей это возможность
кастомизировать UI android-приложений в случаях, когда нет исходного кода.

### Цели
1. Оптимизировать работу с нативными хуками
2. Добавить хуки для `LayoutInflater`
3. и т.д.

### Ограничения
1. Сейчас вы можете делать хуки только для `AssetManager` and `Activity`.
2. Вы можете изменять только предоставляемые атрибуты без добавления и удаления оных.

### Sub-projects:
1. `library` - "ядро" `pygmalion` со всеми API нужными для разработки.
2. `demo` - android-приложение, разработанное как "Галерея" для демонстрации.
3. `stub` - обеспечивает прямой доступ к приватным `android` `api`.

## Юзкейсы
Я настоятельно рекомендую сто раз подумать, прежде чем использовать эту библиотеку в своих проектах.
Она изначально предназначена не для нормальной android-разработки, а для случаев когда нет доступа к
исходному коду. Например, для разработки модификаций android-приложений таких как [Revanced's mods](https://revanced.app/),
[VTLIte](https://github.com/vtosters/lite) и т.д..

## Интеграция
> Скачайте aar последней [Релизной версии](https://github.com/Andromoda/Pygmalion/releases/latest)
> и добавьте его в свой проект

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

## Разработка

### Инициализация
`pygmalion` имеет API для ручного управления хукингом:

```kotlin
/*
* проверяем проинициализировался ли Pygmalion
* и включаем хукинг 
*/
if(Pygmalion.isInitialized()) {
    Pyhmalion.hook()
}
```

```kotlin
//отключаем хукинг
Pygmalion.unhook()
```

### Hooks


#### Добавление/удаление хуков для `AssetManager`:

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
    //Добавляем хуки для AssetManager
    Pygmalion.registerAssetHooks(exampleHook,/*...*/)
}

fun unhook() {
    //Удаляем хуки для AssetManager
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
        //Добавляем хуки для AssetManager
        Pygmalion.registerAssetHooks(hook,hook);
    }
    
    public static void unhook() {
        //Удаляем хуки для AssetManager
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
    //Добавляем хуки для Activity
    Pygmalion.registerActivityLifecycleCallbacks(exampleHook,/*...*/)
}

fun unhook() {
    //Удаляем хуки для Activity
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
        //Добавляем хуки для Activity
        Pygmalion.registerActivityLifecycleCallbacks(hook,hook);
    }

    public static void unhook() {
        //Удаляем хуки для Activity
        Pygmalion.unregisterActivityLifecycleCallbacks(hook,hook);
    }
}
```

#### Подробнее в `demo` и `library`