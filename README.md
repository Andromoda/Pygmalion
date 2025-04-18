## Pygmalion

[English](README.md) | [Russian](README_RU.md)

`pygmalion` is a standalone Android library for customizing the native UI of Android applications by
creating hooks for `AssetManager`, `Activity`, and `LayoutInflater`
**without requiring root permissions, Xposed Framework, etc.**

Supports devices with `Android 5.0 - Android 15+` and `x86`, `x86_64`, `arm32`, and `arm64`
architectures.

> [!CAUTION]
> The library is in **Alpha** status, so backward compatibility with future versions is not
> guaranteed. Developers are also not responsible for any potential consequences of using the
> library.

## Motivation

There are many solutions for Android customization, but they usually rely on root access, Xposed, or
its analogs, or other system-modifying methods to achieve this. I wanted to create a tool that would
enable customization, at least at the level of Android applications, without modifying the system.

## Usage

`pygmalion` is ideal for projects where customization is needed without access to the application's
source code, such as projects like [Revanced's mods](https://revanced.app/)
or [VTLIte](https://github.com/vtosters/lite).

## Limitations

- `pygmalion` is worked only in the applications, where's integrated.
- Supports hooks only for `AssetManager`, `Activity`, and `LayoutInflater`.
- `AssetManager` hooks is not supported adding/removing attributes, only value modifications.

## How It Works

### **Java Level**:

- Provides APIs for creating hooks for `AssetManager`, `Activity`, and `LayoutInflater`
- Provides APIs for initialization, hook management, adding/removing hooks

### **Native Level**:

- Implemented "proxy functions" - functions that replace the original native `AssetManager` functions
and pass resources to the Java layer for modification before returning to the original call point (
this approach allows you to intervene in the resource processing process by implementing your own
logic using hooks).

> [!NOTE]
> For devices with Android N, the library automatically disables the [
`@FastNative`](https://developer.android.com/reference/dalvik/annotation/optimization/FastNative)
> optimization for all `AssetManager` functions, as it may cause crashes.

## Subprojects:

- `library` - the "core" of `pygmalion` with all the APIs needed for development.
- `demo` - a demonstration app showcasing the library's capabilities.
- `stub` - direct access to private APIs.

## Links

- [App resources overview](https://developer.android.com/guide/topics/resources/providing-resources)
- [Activity](https://developer.android.com/reference/android/app/Activity)
- [LayoutInflater](https://developer.android.com/reference/android/view/LayoutInflater)
- [AssetManager](https://developer.android.com/reference/android/content/res/AssetManager)
- [Resources](https://developer.android.com/reference/android/content/res/Resources)
- [TypedValue](https://developer.android.com/reference/android/util/TypedValue)
- [TypedArray](https://developer.android.com/reference/android/content/res/TypedArray)
