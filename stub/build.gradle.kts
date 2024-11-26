plugins {
    alias(libs.plugins.android.library)
}

android {
    namespace="com.vologhat.stub"
    compileSdk=35

    defaultConfig {
        minSdk=28

        testInstrumentationRunner="androidx.test.runner.AndroidJUnitRunner"
        consumerProguardFiles("consumer-rules.pro")
    }

    compileOptions {
        sourceCompatibility=JavaVersion.VERSION_1_8
        targetCompatibility=JavaVersion.VERSION_1_8
    }
}