@file:Suppress("unused")

package com.vologhat.pygmalion.hooks.api

import android.util.TypedValue
import com.vologhat.pygmalion.hooks.STYLE_NUM_ENTRIES
import com.vologhat.pygmalion.hooks.applyStyleHook
import com.vologhat.pygmalion.hooks.loadResourceValueHook
import com.vologhat.pygmalion.hooks.loadThemeAttrValueHook
import com.vologhat.pygmalion.hooks.resolveAttrsHook
import com.vologhat.pygmalion.hooks.retrieveAttrsHook
import com.vologhat.pygmalion.utils.NativeIntArray

object HookPostOreo
{
    @JvmStatic
    fun nativeGetResourceValue(
        ptr:Long,
        resId:Int,
        density:Short,
        outValue:TypedValue,
        resolveRefs:Boolean,
    ):Int
    {
        loadResourceValueHook(resId,density,outValue,resolveRefs)
        return 0
    }
    
    @JvmStatic
    fun nativeThemeGetAttributeValue(
        ptr:Long,
        theme:Long,
        resId:Int,
        outValue:TypedValue,
        resolveRefs:Boolean,
    ):Int
    {
        loadThemeAttrValueHook(resId,outValue,resolveRefs)
        return 0
    }
    
    @JvmStatic
    fun nativeApplyStyle(
        ptr:Long,
        themePtr:Long,
        defStyleAttr:Int,
        defStyleRes:Int,
        xmlParserPtr:Long,
        inAttrs:IntArray,
        outValuesAddress:Long,
        outIndicesAddress:Long,
    )
    {
        val len=inAttrs.size
        val outValues=NativeIntArray(outValuesAddress,len*STYLE_NUM_ENTRIES)
        val outIndices=NativeIntArray(outIndicesAddress,len)
        applyStyleHook(defStyleAttr,defStyleRes,inAttrs,outValues,outIndices)
    }
    
    @JvmStatic
    fun nativeResolveAttrs(
        ptr:Long,
        themePtr:Long,
        defStyleAttr:Int,
        defStyleRes:Int,
        inValues:IntArray,
        inAttrs:IntArray,
        outValues:IntArray,
        outIndices:IntArray,
    ):Boolean
    {
        resolveAttrsHook(defStyleAttr,defStyleRes,inValues,inAttrs,outValues,outIndices)
        return false
    }
    
    @JvmStatic
    fun nativeRetrieveAttributes(
        ptr:Long,
        xmlParserPtr:Long,
        inAttrs:IntArray,
        outValues:IntArray,
        outIndices:
        IntArray,
    ):Boolean
    {
        retrieveAttrsHook(inAttrs,outValues,outIndices)
        return false
    }
}