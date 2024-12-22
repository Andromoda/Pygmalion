import com.kezong.fataar.FatAarExtension
import org.gradle.kotlin.dsl.support.unzipTo
import org.gradle.kotlin.dsl.support.zipTo

buildscript {
    repositories {
        maven {
            url=uri("https://jitpack.io")
            content {
                includeGroup("com.github.aasitnikov")
            }
        }
    }
    dependencies {
        classpath(libs.fatAarAndroid)
    }
}

plugins {
    alias(libs.plugins.android.library)
    alias(libs.plugins.kotlin.android)
}

apply(plugin="com.kezong.fat-aar")
configure< FatAarExtension > {
    transitive=true
}

android {
    namespace="com.vologhat.pygmalion"
    compileSdk=35

    defaultConfig {
        minSdk=28
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
    "embed"(libs.kotlin.stdlib.jdk8)
}

afterEvaluate {
    android.libraryVariants.forEach { variant ->
        val outFile=variant.outputs.first().outputFile
        val tmpDir=outFile.parentFile.resolve("tmp")
        tasks.named("assemble${variant.name.capitalize()}").configure {
            doLast {
                unzipTo(tmpDir,outFile)
                fileTree(tmpDir).matching {
                    include("libs/*.jar")
                }.forEach { lib ->
                    val libDir=lib.parentFile.resolve(lib.nameWithoutExtension)
                    unzipTo(libDir,lib)
                    libDir.apply {
                        //remove difficult files
                        resolve("META-INF").deleteRecursively()
                    }
                    lib.delete()
                    if(fileTree(libDir).isEmpty)return@forEach
                    zipTo(lib,libDir)
                    libDir.deleteRecursively()
                }
                outFile.delete()
                zipTo(outFile.parentFile.resolve("pygmalion-${variant.name}.aar"),tmpDir)
                tmpDir.deleteRecursively()
            }
        }
    }
}