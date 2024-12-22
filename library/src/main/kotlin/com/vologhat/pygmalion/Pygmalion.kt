@file:JvmName("Pygmalion")

package com.vologhat.pygmalion

import android.annotation.SuppressLint
import android.app.Application
import android.content.res.Resources
import android.util.TypedValue
import androidx.annotation.Discouraged
import com.vologhat.pygmalion.hooks.IAssetHook

object Pygmalion
{
    /** Global application instance */
    @SuppressLint("PrivateApi")
    @JvmField
    val app=
        run {
            val appGlobalsClz=Class.forName("android.app.AppGlobals")
            val getInitialApplicationMtd=
                appGlobalsClz.getDeclaredMethod("getInitialApplication")
                    .apply { isAccessible=true }
            getInitialApplicationMtd.invoke(null) as Application
        }
    
    /** System resources */
    @JvmStatic
    inline val systemResources
        get()=Resources.getSystem()
    
    /** Application resources */
    @JvmStatic
    val resources
        get()=app.resources
    
    /** The activity callbacks for Pygmalion */
    private val activityCallbacks=mutableSetOf<Application.ActivityLifecycleCallbacks>()
    
    /** The asset hooks */
    @JvmField
    internal val assetHooks=mutableSetOf<IAssetHook>()
    
    init
    {
        System.loadLibrary("pygmalion")
    }
    
    /** Checks if initialized successfully */
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
    
    @JvmStatic
    fun unregisterAllAssetHooks()=
        unregisterAssetHooks(*assetHooks.toTypedArray())
    
    /** Unregister [hooks] */
    @JvmStatic
    fun unregisterAssetHooks(vararg hooks:IAssetHook)=
        assetHooks.removeAll(hooks)
    
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