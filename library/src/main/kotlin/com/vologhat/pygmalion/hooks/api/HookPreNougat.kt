package com.vologhat.pygmalion.hooks.api

import android.util.TypedValue
import com.vologhat.pygmalion.hooks.applyStyleHookLegacy
import com.vologhat.pygmalion.hooks.loadResourceValueHook
import com.vologhat.pygmalion.hooks.loadThemeAttrValueHook
import com.vologhat.pygmalion.hooks.resolveAttrsHook
import com.vologhat.pygmalion.hooks.retrieveAttrsHook

object HookPreNougat
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
        outValues:IntArray,
        outIndices:IntArray
    ):Boolean
    {
        applyStyleHookLegacy(
            defStyleAttr,
            defStyleRes,
            inAttrs,
            outValues,
            outIndices
        )
        return false
    }
    
    @JvmStatic
    fun resolveAttrs(
        theme:Long,
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
    fun retrieveAttributes(
        xmlParser:Long,
        inAttrs:IntArray,
        outValues:IntArray,
        outIndices:IntArray,
    ):Boolean
    {
        retrieveAttrsHook(inAttrs,outValues,outIndices)
        return false
    }
}

