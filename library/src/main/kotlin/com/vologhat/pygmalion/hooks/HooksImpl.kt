@file:Suppress("unused")

package com.vologhat.pygmalion.hooks

import android.os.Build
import android.util.TypedValue
import androidx.annotation.RequiresApi
import com.vologhat.pygmalion.Pygmalion.assetHooks
import com.vologhat.pygmalion.utils.NativeIntArray

@JvmField
internal val STYLE_NUM_ENTRIES=
    if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.Q)7
    else 6
internal const val STYLE_TYPE=0
internal const val STYLE_DATA=1
internal const val STYLE_ASSET_COOKIE=2
internal const val STYLE_RESOURCE_ID=3
internal const val STYLE_CHANGING_CONFIGURATIONS=4
internal const val STYLE_DENSITY=5
@RequiresApi(Build.VERSION_CODES.Q)
internal const val STYLE_SOURCE_RESOURCE_ID=6

private fun interface IIndexedProvider
{
    operator fun get(index:Int):Int
}
private fun interface IIndexedSupplier
{
    operator fun set(index:Int,value:Int)
}

private typealias ValuesProvider=IndicesProvider
private typealias IndicesProvider=IIndexedProvider
private typealias ValuesSupplier=IIndexedSupplier

internal fun loadResourceValueHook(
    resId:Int,
    density:Short,
    outValue:TypedValue,
    resolveAttributes:Boolean
)=assetHooks.forEach { hook ->
    hook.onLoadResourceValueHook(resId,outValue,resolveAttributes)
}

internal fun loadThemeAttrValueHook(
    resId:Int,
    outValue:TypedValue,
    resolveAttrs:Boolean
)=assetHooks.forEach { hook ->
    hook.onLoadThemeAttrValueHook(resId,outValue,resolveAttrs)
}

internal fun applyStyleHook(
    defStyleAttr:Int,
    defStyleRes:Int,
    inAttrs:IntArray,
    outValues:NativeIntArray,
    outIndices:NativeIntArray
)
{
    val outTypedValued=unpackValues(inAttrs.size,outValues::get)
    assetHooks.forEach { hook ->
        hook.onApplyStyleHook(defStyleAttr,defStyleRes,inAttrs,outTypedValued)
    }
    packValues(outTypedValued,outValues::set)
}

internal fun resolveAttrsHook(
    defStyleAttr:Int,
    defStyleRes:Int,
    inValues:IntArray,
    inAttrs:IntArray,
    outValues:IntArray,
    outIndices:IntArray
)
{
    val outTypedValued=unpackValues(inAttrs.size,outValues::get)
    assetHooks.forEach { hook ->
        hook.onResolveAttrsHook(defStyleAttr,defStyleRes,inValues,inAttrs,outTypedValued)
    }
    packValues(outTypedValued,outValues::set)
}

internal fun retrieveAttrsHook(
    inAttrs:IntArray,
    outValues:IntArray,
    outIndices:IntArray
)
{
    val outTypedValued=unpackValues(inAttrs.size,outValues::get)
    assetHooks.forEach { hook ->
        hook.onRetrieveAttrsHook(inAttrs,outTypedValued)
    }
    packValues(outTypedValued,outValues::set)
}

private fun unpackValues(length:Int,values:ValuesProvider)=
    MutableList(length) { index ->
        unpackValue(index*STYLE_NUM_ENTRIES,values)
    }

private fun unpackValue(index:Int,values:ValuesProvider)=
    TypedValue().apply {
        type=values[index+STYLE_TYPE]
        data=values[index+STYLE_DATA]
        assetCookie=values[index+STYLE_ASSET_COOKIE]
        resourceId=values[index+STYLE_RESOURCE_ID]
        changingConfigurations=values[index+STYLE_CHANGING_CONFIGURATIONS]
        density=values[index+STYLE_DENSITY]
        if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.Q)sourceResourceId=values[index+STYLE_SOURCE_RESOURCE_ID]
    }

private fun packValues(values:List< TypedValue >,valuesProvider:ValuesSupplier)=
    values.forEachIndexed { index,value ->
        packValue(index*STYLE_NUM_ENTRIES,value,valuesProvider)
    }

private fun packValue(index:Int,value:TypedValue,values:ValuesSupplier)
{
    values[index+STYLE_TYPE]=value.type
    values[index+STYLE_DATA]=value.data
    values[index+STYLE_ASSET_COOKIE]=value.assetCookie
    values[index+STYLE_RESOURCE_ID]=value.resourceId
    values[index+STYLE_CHANGING_CONFIGURATIONS]=value.changingConfigurations
    values[index+STYLE_DENSITY]=value.density
    if(Build.VERSION.SDK_INT>Build.VERSION_CODES.P)values[index+STYLE_SOURCE_RESOURCE_ID]=value.sourceResourceId
}