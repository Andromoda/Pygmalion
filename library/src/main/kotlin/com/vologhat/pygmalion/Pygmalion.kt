@file:JvmName("Pygmalion")

package com.vologhat.pygmalion

import android.annotation.SuppressLint
import android.app.AppGlobals
import android.app.Application
import android.content.res.Resources
import android.util.TypedValue
import android.view.LayoutInflater
import androidx.annotation.Discouraged
import com.vologhat.pygmalion.hooks.IAssetHook
import com.vologhat.pygmalion.inflater.PygmalionFactory2
import com.vologhat.pygmalion.utils.forceSetFactory2

@Suppress("KotlinJniMissingFunction")
object Pygmalion
{
    /** Global application instance */
    val app by lazy {
        AppGlobals.getInitialApplication()
    }

    /** System resources */
    @JvmStatic
    inline val systemResources
        get()=Resources.getSystem()

    /** Application resources */
    @JvmStatic
    inline val resources
        get()=app.resources

    /** The activity callbacks for Pygmalion */
    private val activityCallbacks=mutableSetOf<Application.ActivityLifecycleCallbacks>()

    /** The asset hooks */
    @JvmField
    internal val assetHooks=mutableSetOf<IAssetHook>()
    
    private var isLibraryLoaded=false

    /** Initializes pygmalion */
    fun initialize()
    {
        if(!isLibraryLoaded)System.loadLibrary("pygmalion")
    }

    /** Checks if pygmalion initialized successfully */
    @JvmStatic
    external fun isInitialized():Boolean

    /** Enables hooking */
    @JvmStatic
    external fun hook():Boolean

    /** Disables hooking */
    @JvmStatic
    external fun unhook():Boolean

    /** @see Application.registerActivityLifecycleCallbacks */
    @JvmStatic
    fun registerActivityLifecycleCallbacks(vararg callbacks:Application.ActivityLifecycleCallbacks)=
        callbacks.forEach(app::registerActivityLifecycleCallbacks)

    /** @see Application.unregisterActivityLifecycleCallbacks */
    @JvmStatic
    fun unregisterAllActivityLifecycleCallbacks()=
        unregisterActivityLifecycleCallbacks(*activityCallbacks.toTypedArray())

    /** @see Application.unregisterActivityLifecycleCallbacks */
    @JvmStatic
    fun unregisterActivityLifecycleCallbacks(vararg callbacks:Application.ActivityLifecycleCallbacks)=
        callbacks.forEach(app::unregisterActivityLifecycleCallbacks)

    /** Register [hooks] */
    @JvmStatic
    fun registerAssetHooks(vararg hooks:IAssetHook)=
        assetHooks.addAll(hooks)

    /** Unregister all asset hooks */
    @JvmStatic
    fun unregisterAllAssetHooks()=
        unregisterAssetHooks(*assetHooks.toTypedArray())

    /** Unregister [hooks] */
    @JvmStatic
    fun unregisterAssetHooks(vararg hooks:IAssetHook)=
        assetHooks.removeAll(hooks)

    /** Attach pygmalion's [LayoutInflater.Factory2] to target [inflater] */
    @JvmStatic
    fun attachToLayoutInflater(inflater:LayoutInflater):PygmalionFactory2
    {
        if(inflater.factory2 !is PygmalionFactory2)
        {
            val newFactory2=PygmalionFactory2()
            inflater.forceSetFactory2(newFactory2)
            return newFactory2
        }
        return inflater.factory2 as PygmalionFactory2
    }
    
    /** Detaches pygmalion's [LayoutInflater.Factory2] from target [inflater] */
    @JvmStatic
    fun detachFromLayoutInflater(inflater:LayoutInflater)
    {
        val factory2=inflater.factory2
        if(factory2 is PygmalionFactory2)inflater.forceSetFactory2(factory2.original)
    }

    /**
     * The analogue of [Resources.getValue]
     * where you don't need to pass [outValue] every time
     *
     * @see [Resources.getValue]
     */
    @JvmStatic
    @JvmOverloads
    fun getValue(
        resId:Int,
        resolveRefs:Boolean=true,
        source:Resources=resources,
        outValue:TypedValue=TypedValue(),
    )=outValue.also { source.getValue(resId,it,resolveRefs) }

    /**
     * The analogue of [Resources.getValue]
     * where you don't need to pass [outValue] every time.
     * In addition, you can access resource by their short
     * or fully qualified [name].
     *
     * @see [Resources.getIdentifier]
     * @see [Resources.getValue]
     */
    @Discouraged(
        message="Usage of this function is discouraged. "+
                "Recommends to retrieve resources by their identifiers."
    )
    @SuppressLint("DiscouragedApi")
    @JvmStatic
    @JvmOverloads
    fun getValue(
        name:String,
        defType:String?=null,
        defPackage:String?=null,
        resolveRefs:Boolean=true,
        source:Resources=resources,
        outValue:TypedValue=TypedValue(),
    )=outValue.also {
        when
        {
            !defType.isNullOrBlank()&&!defPackage.isNullOrBlank() ->
            {
                val resId=source.getIdentifier(name,defType,defPackage)
                getValue(resId,resolveRefs,source,it)
            }

            else -> source.getValue(name,it,resolveRefs)
        }
    }
}