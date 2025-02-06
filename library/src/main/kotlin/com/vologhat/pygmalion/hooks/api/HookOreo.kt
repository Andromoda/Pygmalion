@file:Suppress("unused")

package com.vologhat.pygmalion.hooks.api

import android.util.TypedValue
import com.vologhat.pygmalion.hooks.applyStyleHook
import com.vologhat.pygmalion.hooks.loadResourceValueHook
import com.vologhat.pygmalion.hooks.loadThemeAttrValueHook
import com.vologhat.pygmalion.hooks.resolveAttrsHook
import com.vologhat.pygmalion.hooks.retrieveAttrsHook
import com.vologhat.pygmalion.utils.NativeIntArray

object HookOreo
{
    @JvmStatic
    fun loadResourceValue(
        ident:Int,
        density:Short,
        outValue:TypedValue,
        resolve:Boolean,
    ):Int
    {
        loadResourceValueHook(ident,density,outValue,resolve)
        return 0
    }
    
    @JvmStatic
    fun loadThemeAttributeValue(
        theme:Long,
        ident:Int,
        outValue:TypedValue,
        resolve:Boolean,
    ):Int
    {
        loadThemeAttrValueHook(ident,outValue,resolve)
        return 0
    }
    
    @JvmStatic
    fun applyStyle(
        theme:Long,
        defStyleAttr:Int,
        defStyleRes:Int,
        xmlParser:Long,
        inAttrs:IntArray,
        length:Int,
        outValuesAddress:Long,
        outIndicesAddress:Long,
    )
    {
        applyStyleHook(
            defStyleAttr,
            defStyleRes,
            inAttrs,
            NativeIntArray(outValuesAddress,length),
            NativeIntArray(outValuesAddress,length)
        )
    }
    
    @JvmStatic
    fun resolveAttrs(
        theme:Long,
        defStyleAttr:Int,
        defStyleRes:Int,
        inValues:IntArray,
        intAttrs:IntArray,
        outValues:IntArray,
        outIndices:IntArray,
    ):Boolean
    {
        resolveAttrsHook(defStyleAttr,defStyleRes,inValues,intAttrs,outValues,outIndices)
        return false
    }
    
    @JvmStatic
    fun retrieveAttributes(
        xmlParser:Long,
        intAttrs:IntArray,
        outValues:IntArray,
        outIndices:IntArray,
    ):Boolean
    {
        retrieveAttrsHook(intAttrs,outValues,outIndices)
        return false
    }
}