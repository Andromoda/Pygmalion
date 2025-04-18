plugins {
    alias(libs.plugins.android.library)
    alias(libs.plugins.kotlin.android)
}

android {
    namespace="com.vologhat.pygmalion"
    compileSdk=35

    defaultConfig {
        minSdk=21
        multiDexEnabled=false

        testInstrumentationRunner="androidx.test.runner.AndroidJUnitRunner"
        consumerProguardFiles("consumer-rules.pro")
    }

    buildTypes {
        release {
            isMinifyEnabled=false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    externalNativeBuild {
        cmake {
            path("src/main/cpp/CMakeLists.txt")
        }
    }
    compileOptions {
        sourceCompatibility=JavaVersion.VERSION_1_8
        targetCompatibility=JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        javaParameters=true
        jvmTarget="1.8"
        freeCompilerArgs+=listOf("-Xjvm-default=all")
    }
}

dependencies {
    compileOnly(project(":stub"))

    implementation(libs.androidx.annotation.jvm)
    implementation(libs.hiddenapibypass)
}