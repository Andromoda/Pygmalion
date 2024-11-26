package com.vologhat.pygmalion.hooks

import android.util.TypedValue
import android.content.res.TypedArray

/**
 * The container used to pass information about single [TypedValue]
 */
class Asset internal constructor(
    val resId:Int,
    val outValue:TypedValue,
    val resolveAttrs:Boolean
)

/**
 * The container used to pass information about [TypedArray]
 * because we can't use [TypedArray] directly
 */
class Assets internal constructor(
    val defStyleAttr:Int=0,
    val defStyleRes:Int=0,
    val inValues:IntArray=intArrayOf(),
    val inAttrs:IntArray,
    val outValues:List< TypedValue >
)

private class AssetHookDelegate(
    private val onLoadResourceValueBlock:(Asset) -> Unit,
    private val onLoadThemeAttrValueBlock:(Asset) -> Unit,
    private val onApplyStyleBlock:(Assets) -> Unit,
    private val onResolveAttrsBlock:(Assets) -> Unit,
    private val onRetrieveAttrsBlock:(Assets) -> Unit
):IAssetHook
{
    override fun onLoadResourceValueHook(
        resId:Int,
        outValue:TypedValue,
        resolveAttrs:Boolean
    )
    {
        onLoadResourceValueBlock(
            Asset(resId,outValue,resolveAttrs)
        )
    }

    override fun onLoadThemeAttrValueHook(
        resId:Int,
        outValue:TypedValue,
        resolveAttrs:Boolean
    ) {
        onLoadThemeAttrValueBlock(
            Asset(resId,outValue,resolveAttrs)
        )
    }

    override fun onApplyStyleHook(
        defStyleAttr:Int,
        defStyleRes:Int,
        inAttrs:IntArray,
        outValues:List< TypedValue >
    )
    {
        onApplyStyleBlock(
            Assets(
                defStyleAttr=defStyleAttr,
                defStyleRes=defStyleRes,
                inAttrs=inAttrs,
                outValues=outValues
            )
        )
    }

    override fun onResolveAttrsHook(
        defStyleAttr:Int,
        defStyleRes:Int,
        inValues:IntArray,
        inAttrs:IntArray,
        outValues:List< TypedValue >
    )
    {
        onResolveAttrsBlock(
            Assets(
                defStyleAttr=defStyleAttr,
                defStyleRes=defStyleRes,
                inValues=inValues,
                inAttrs=inAttrs,
                outValues=outValues
            )
        )
    }

    override fun onRetrieveAttrsHook(
        inAttrs:IntArray,
        outValues:List< TypedValue >
    )
    {
        onRetrieveAttrsBlock(
            Assets(
                inAttrs=inAttrs,
                outValues=outValues
            )
        )
    }
}

class AssetHookBuilder internal constructor()
{
    private var onLoadResourceValueBlock:Asset.() -> Unit={}
    private var onLoadThemeAttrValueBlock:Asset.() -> Unit={}
    private var onApplyStyleBlock:Assets.() -> Unit={}
    private var onResolveAttrsBlock:Assets.() -> Unit={}
    private var onRetrieveAttrsBlock:Assets.() -> Unit={}

    @JvmSynthetic
    fun onLoadResourceValue(block:(asset:Asset) -> Unit)
    { onLoadResourceValueBlock=block }

    @JvmSynthetic
    fun onLoadThemeAttrValue(block:(asset:Asset) -> Unit)
    { onLoadThemeAttrValueBlock=block }

    @JvmSynthetic
    fun onApplyStyle(block:(assets:Assets) -> Unit)
    { onApplyStyleBlock=block }

    @JvmSynthetic
    fun onResolveAttrs(block:(assets:Assets) -> Unit)
    { onResolveAttrsBlock=block }

    @JvmSynthetic
    fun onRetrieveAttrs(block:(assets:Assets) -> Unit)
    { onRetrieveAttrsBlock=block }

    @JvmSynthetic
    internal fun build():IAssetHook=
        AssetHookDelegate(
            onLoadResourceValueBlock,
            onLoadThemeAttrValueBlock,
            onApplyStyleBlock,
            onResolveAttrsBlock,
            onRetrieveAttrsBlock
        )
}

@JvmSynthetic
fun assetHook(block:AssetHookBuilder.() -> Unit)=
    AssetHookBuilder().apply(block).build()