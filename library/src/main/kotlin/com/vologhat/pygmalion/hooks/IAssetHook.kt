package com.vologhat.pygmalion.hooks;

import android.content.res.Resources
import android.util.TypedValue

typealias TypedValuesList=List< @JvmSuppressWildcards TypedValue >

/** The asset hook interface */
interface IAssetHook
{
    /** See [Resources.getValue] */
    fun onLoadResourceValueHook(
        resId:Int,
        outValue:TypedValue,
        resolveAttrs:Boolean
    )
    { }

    /** See [Resources.Theme.resolveAttribute] */
    fun onLoadThemeAttrValueHook(
        resId:Int,
        outValue:TypedValue,
        resolveAttrs:Boolean
    )
    { }

    /** See [Resources.Theme.obtainStyledAttributes] */
    fun onApplyStyleHook(
        defStyleAttr:Int,
        defStyleRes:Int,
        inAttrs:IntArray,
        outValues:TypedValuesList
    )
    { }

    /** See [Resources.Theme.resolveAttribute] */
    fun onResolveAttrsHook(
        defStyleAttr:Int,
        defStyleRes:Int,
        inValues:IntArray,
        inAttrs:IntArray,
        outValues:TypedValuesList
    )
    { }

    /** See [Resources.Theme.obtainAtributes] */
    fun onRetrieveAttrsHook(
        inAttrs:IntArray,
        outValues:TypedValuesList
    )
    { }
}
