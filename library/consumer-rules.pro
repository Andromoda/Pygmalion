-keep class com.vologhat.pygmalion.hooks.api.* {
    public static *;
}
-keep class com.vologhat.pygmalion.Pygmalion {
    isInitialized();
    hook();
    unhook();
}