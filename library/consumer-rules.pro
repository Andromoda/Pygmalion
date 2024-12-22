-keep class com.vologhat.pygmalion.Pygmalion {
    public *;
}

-keep class com.vologhat.pygmalion.lifecycle.IActivityLifecycleCallback {
    public *;
}

-keep,allowobfuscation class com.vologhat.pygmalion.lifecycle.ActivityLifecycleCallbacks, com.vologhat.pygmalion.lifecycle.ActivityLifecycleCallbackBuilder
-keepclasseswithmembers class com.vologhat.pygmalion.lifecycle.ActivtyLifecycleCallbackKt

-keep class com.vologhat.pygmalion.hooks.api.* {
    public static *;
}

-keepclasseswithmembers class com.vologhat.pygmalion.utils.*