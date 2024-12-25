## Pygmalion

[English](README.md) | [Русский](README_RU.md)

`pygmalion` это автономная `non-root` `android` библиотека, необходимая для кастомизации UI android-приложений
посредством создания хуков для `AssetManager` и `Activity`

Поддерживаются устройства с `Android 5.0 - Android 15` и `x86`, `x86_64`, `arm32`, и `arm64` архитектурами.

> [!CAUTION]
> Я и контрибьютеры не несём ответственности за любой приченённый вред, вызванный
> использованием этой библиотеки в ваших проектах. Также этот проект находится в альфа-стадии, поэтому
> **обратная совметимость с будущими обновлениями не гарантируется.** 

## Мотивация
Изначально это была странная идея создания средства для кастомизации приложений без использования `root`, `xposed` и т.п.,
и я не планировал использовать натив от слова совсем. Но, как оказалось, это был единственный нормальный
способ осуществить мою задумку перехвата вызовов `AssetManager`. Помимо этого я не хочу использовать известные 
`ART hooking` фреймворки из-за их нестабильности по сравнению с моим методов.

## Описание проекта
`pygmalion` нужен для тех случаев, когда требуется реализовать кастомизацию приложений
(пр. изменение акцентных цветов) без исходного кода.
Чтобы использовать эту библиотеку, нужно знать про **комплексные** и **примитивные (хранящие простые значения)** ресурсы
(см. [App resources overview](https://developer.android.com/guide/topics/resources/providing-resources)).
Также вы можете ознакомиться с исходным кодом [AssetManager](https://cs.android.com/android/platform/superproject/main/+/main:frameworks/base/core/java/android/content/res/AssetManager.java),
[Resources](https://cs.android.com/android/platform/superproject/main/+/main:frameworks/base/core/java/android/content/res/Resources.java),
[TypedValue](https://cs.android.com/android/platform/superproject/main/+/main:frameworks/base/core/java/android/util/TypedValue.java)
и [TypedArray](https://cs.android.com/android/platform/superproject/main/+/main:frameworks/base/core/java/android/content/res/TypedArray.java)
**для определённых платформ**.

## Принцип работы
`pygmalion` работает на двух уровнях:
- **Java-уровень** предоставляет API для создания хуков для `AssetManager` и `Activity`
- **Нативный уровень** используется для перехвата собственных `JNI` функций `AssetManager`, связанных с ресурсами, путем перерегистрации оных, для
дальнейших манипуляций с извлеченными данными (идентификаторами атрибутов, значениями ресурсов и т. д.) до того, как они будут возвращены.

В **нативе** `pygmalion` перехватывает функцию с сигнатурой `_ZN7android37register_android_content_AssetManagerEP7_JNIEnv`,
которая используется для регистрации всех `JNI` функций `AssetManager`, и дампит исходные адреса функций. Затем целевые функции находятся по жестко-закодированным сигнатурам и заменяются на функции-заглушки, которые вызывают
Java-функции с реализацией логики. Этот способ более стабилен, чем многие `ART hooking` фреймфорки, потому что там
используется встроенный `JNI` API и проверенные библиотеки.

> [!NOTE]
> Для Android N `pygmalion` отключает `@FastNative` оптимизации,
которые приводят к сбоям.

> [!TIP]
> Более подробную информацию см. в заголовках в `include/hooks/assetman/api` для натива
> и `com.vologhat.pygmalion.hooks` для Java

## TODO
- Оптимизировать работу с нативными хуками
- Добавить хуки для `LayoutInflater`
- и т.д.

## Ограничения
1. Сейчас вы можете делать хуки только для `AssetManager` and `Activity`.
2. В хуках `AssetManager` вы можете заменить только предоставленные ресурсы
(пр. вы не можете добавить/удалить атрибут цвета с соответствующим значением)

## Подпроекты:
- `library` - "ядро" `pygmalion` со всеми API нужными для разработки.
- `demo` - android приложение, разработанное как "галерея" для демонстрации.
- `stub` - обеспечивает прямой доступ к приватным `android` `api`.

## Юзкейсы
Я настоятельно рекомендую сто раз подумать, прежде чем использовать эту библиотеку в своих проектах.
Она изначально предназначена не для нормальной android-разработки, а для случаев когда нет доступа к
исходному коду. Например, для разработки модификаций android-приложений таких как [Revanced's mods](https://revanced.app/),
[VTLIte](https://github.com/vtosters/lite) и т.д.

## Интеграция
> [!NOTE]
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
`pygmalion` имеет API для ручного управления:

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