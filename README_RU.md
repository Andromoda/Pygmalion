## Pygmalion

[English](README.md) | [Русский](README_RU.md)

`pygmalion` это автономная Android-библиотека, необходимая для кастомизации нативного UI
Android-приложений
посредством создания хуков для `AssetManager`, `Activity` и `LayoutInflater` **без root-прав, Xposed
Framework и т.п.**

Поддерживаются устройства с `Android 5.0 - Android 15+` и `x86`, `x86_64`, `arm32`, и `arm64`
архитектурами.

> [!CAUTION]
> Библиотека находится в **альфа-версии**, поэтому обратная совместимость с будущими версиями не
> гарантируется.
> Кроме того, разработчики не несут ответственности за возможные последствия использования
> библиотеки.

## Мотивация

Есть множество решений по кастомизации Android, но, как правило, они используют root-права, Xposed и
его аналоги
или иные средства, модифицирующие систему, чтобы достичь оного. Я хотел создать средство, которое
позволило бы
добиться возможности кастомизации хотя бы на уровне Android-приложений, но не модифицируя систему.

## Применение

`pygmalion` идеально подходит для проектов, где необходимо реализовать кастомизацию без доступа к
исходному коду приложения, например, для таких проектов,
как [Revanced's mods](https://revanced.app/) или [VTLIte](https://github.com/vtosters/lite).

## Ограничения

- `pygmalion` работает только внутри приложений, куда он интегрирован
- Создание хуков возможно только для `AssetManager`, `Activity` и `LayoutInflater`
- При создании хуков для `AssetManager` нельзя добавлять или удалять атрибуты, можно только менять
  значения

## Принцип работы

### **Java-уровень**:

- Предоставляются API для создания хуков для `AssetManager`, `Activity`, и `LayoutInflater`
- Предоставляются API для инициализации, управления хукингом, добавления/удаления хуков

### **Нативный уровень**:

- Реализованы "прокси-функции" - функции, заменяющие оригинальные нативные функции `AssetManager` и передающие ресурсы на Java-уровень для их модификации перед возвратом в исходную точку
  вызова (такой подход позволяет вмешиваться в процесс обработки ресурсов, реализуя собственную логику
  посредством хуков).

> [!NOTE]
> Для устройств с **Android N** библиотека автоматически отключает оптимизацию [
`@FastNative`](https://developer.android.com/reference/dalvik/annotation/optimization/FastNative)
> для всех функций AssetManager, так как это может вызвать сбои.

## Подпроекты:

- `library` - "ядро" `pygmalion` со всеми API нужными для разработки.
- `demo` - демонстрационное приложение, показывающее возможности библиотеки.
- `stub` - доступ к приватным API напрямую.

## Ссылки

- [App resources overview](https://developer.android.com/guide/topics/resources/providing-resources)
- [Activity](https://developer.android.com/reference/android/app/Activity)
- [LayoutInflater](https://developer.android.com/reference/android/view/LayoutInflater)
- [AssetManager](https://developer.android.com/reference/android/content/res/AssetManager)
- [Resources](https://developer.android.com/reference/android/content/res/Resources)
- [TypedValue](https://developer.android.com/reference/android/util/TypedValue)
- [TypedArray](https://developer.android.com/reference/android/content/res/TypedArray)