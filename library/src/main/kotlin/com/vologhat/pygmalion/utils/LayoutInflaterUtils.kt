package com.vologhat.pygmalion.utils

import android.os.Build
import android.util.Log
import android.view.LayoutInflater
import org.lsposed.hiddenapibypass.HiddenApiBypass
import java.lang.reflect.Field

private var checked=false
private var factory2Fld:Field?=null

private fun init()
{
    //for future restrictions
    if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.P)
        HiddenApiBypass.addHiddenApiExemptions("Landroid/view/LayoutInflater;")
    runCatching {
        factory2Fld=LayoutInflater::class.java.getDeclaredField("mFactory2")
            .apply { isAccessible=true }
    }.onFailure { cause ->
        when(cause)
        {
            is NoSuchFieldException ->
            {
                Log.e(
                    "Pygmalion","""
                    forceSetFactory2 Could not find field 'mFactory2' on class ${LayoutInflater::class.java}; inflation may have unexpected results.
                """.trimIndent(),cause
                )
            }
        }
    }
    checked=true
}

//using method from https://developer.android.com/reference/android/support/v4/view/LayoutInflaterCompat.html#setfactory2
//to force set our factory2
internal fun LayoutInflater.forceSetFactory2(factory2:LayoutInflater.Factory2?)
{
    if(!checked)init()
    factory2Fld?.let { fld ->
        runCatching {
            fld.set(this,factory2)
        }.onFailure { cause ->
            when(cause)
            {
                is IllegalStateException ->
                {
                    Log.e(
                        "Pygmalion",
                        "forceSetFactory2 could not set the Factory2 on ${this}; inflation may have unexpected results.",
                        cause
                    )
                }
            }
        }
    }
}