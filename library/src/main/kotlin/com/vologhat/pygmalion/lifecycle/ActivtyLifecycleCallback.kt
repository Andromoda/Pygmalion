@file:JvmSynthetic
package com.vologhat.pygmalion.lifecycle

import android.app.Activity
import android.os.Bundle

typealias ActivityCallback = (activity: Activity) -> Unit
typealias ActivityBundleCallback = (activity:Activity,savedInstanceState:Bundle?) -> Unit

typealias OnActivityPreCreatedCallback = ActivityBundleCallback
typealias OnActivityCreatedCallback = ActivityBundleCallback
typealias OnActivityPostCreatedCallback = ActivityBundleCallback
typealias OnActivityPreStartedCallback = ActivityCallback
typealias OnActivityStartedCallback = ActivityCallback
typealias OnActivityPostStartedCallback = ActivityCallback
typealias OnActivityPreResumedCallback = ActivityCallback
typealias OnActivityResumedCallback = ActivityCallback
typealias OnActivityPostResumedCallback = ActivityCallback
typealias OnActivityPrePausedCallback = ActivityCallback
typealias OnActivityPausedCallback = ActivityCallback
typealias OnActivityPostPausedCallback = ActivityCallback
typealias OnActivityPreStoppedCallback = ActivityCallback
typealias OnActivityStoppedCallback = ActivityCallback
typealias OnActivityPostStoppedCallback = ActivityCallback
typealias OnActivityPreSaveInstanceStateCallback = ActivityBundleCallback
typealias OnActivitySaveInstanceStateCallback = ActivityBundleCallback
typealias OnActivityPostSaveInstanceStateCallback = ActivityBundleCallback
typealias OnActivityPreDestroyedCallback = ActivityCallback
typealias OnActivityDestroyedCallback = ActivityCallback
typealias OnActivityPostDestroyedCallback = ActivityCallback

class ActivityLifecycleCallbacks internal constructor(
    private val onPreCreated:OnActivityPreCreatedCallback?=null,
    private val onCreated: OnActivityCreatedCallback?=null,
    private val onPostCreated: OnActivityPostCreatedCallback?=null,
    private val onPreStarted: OnActivityPreStartedCallback?=null,
    private val onStarted: OnActivityStartedCallback?=null,
    private val onPostStarted: OnActivityPostStartedCallback?=null,
    private val onPreResumed: OnActivityPreResumedCallback?=null,
    private val onResumed: OnActivityResumedCallback?=null,
    private val onPostResumed: OnActivityPostResumedCallback? = null,
    private val onPrePaused: OnActivityPrePausedCallback? = null,
    private val onPaused: OnActivityPausedCallback? = null,
    private val onPostPaused: OnActivityPostPausedCallback? = null,
    private val onPreStopped: OnActivityPreStoppedCallback? = null,
    private val onStopped: OnActivityStoppedCallback? = null,
    private val onPostStopped: OnActivityPostStoppedCallback? = null,
    private val onPreSaveInstanceState: OnActivityPreSaveInstanceStateCallback? = null,
    private val onSaveInstanceState: OnActivitySaveInstanceStateCallback? = null,
    private val onPostSaveInstanceState: OnActivityPostSaveInstanceStateCallback? = null,
    private val onPreDestroyed: OnActivityPreDestroyedCallback? = null,
    private val onDestroyed: OnActivityDestroyedCallback? = null,
    private val onPostDestroyed: OnActivityPostDestroyedCallback? = null
):IActivityLifecycleCallback
{
    override fun onActivityPreCreated(activity: Activity, savedInstanceState: Bundle?) {
        onPreCreated?.invoke(activity, savedInstanceState)
    }

    override fun onActivityCreated(activity: Activity, savedInstanceState: Bundle?) {
        onCreated?.invoke(activity, savedInstanceState)
    }

    override fun onActivityPostCreated(activity: Activity, savedInstanceState: Bundle?) {
        onPostCreated?.invoke(activity, savedInstanceState)
    }

    override fun onActivityPreStarted(activity: Activity) {
        onPreStarted?.invoke(activity)
    }

    override fun onActivityStarted(activity: Activity) {
        onStarted?.invoke(activity)
    }

    override fun onActivityPostStarted(activity: Activity) {
        onPostStarted?.invoke(activity)
    }

    override fun onActivityPreResumed(activity: Activity) {
        onPreResumed?.invoke(activity)
    }

    override fun onActivityResumed(activity: Activity) {
        onResumed?.invoke(activity)
    }

    override fun onActivityPostResumed(activity: Activity) {
        onPostResumed?.invoke(activity)
    }

    override fun onActivityPrePaused(activity: Activity) {
        onPrePaused?.invoke(activity)
    }

    override fun onActivityPaused(activity: Activity) {
        onPaused?.invoke(activity)
    }

    override fun onActivityPostPaused(activity: Activity) {
        onPostPaused?.invoke(activity)
    }

    override fun onActivityPreStopped(activity: Activity) {
        onPreStopped?.invoke(activity)
    }

    override fun onActivityStopped(activity: Activity) {
        onStopped?.invoke(activity)
    }

    override fun onActivityPostStopped(activity: Activity) {
        onPostStopped?.invoke(activity)
    }

    override fun onActivityPreSaveInstanceState(activity: Activity, outState: Bundle) {
        onPreSaveInstanceState?.invoke(activity, outState)
    }

    override fun onActivitySaveInstanceState(activity: Activity, outState: Bundle) {
        onSaveInstanceState?.invoke(activity, outState)
    }

    override fun onActivityPostSaveInstanceState(activity: Activity, outState: Bundle) {
        onPostSaveInstanceState?.invoke(activity, outState)
    }

    override fun onActivityPreDestroyed(activity: Activity) {
        onPreDestroyed?.invoke(activity)
    }

    override fun onActivityDestroyed(activity: Activity) {
        onDestroyed?.invoke(activity)
    }

    override fun onActivityPostDestroyed(activity: Activity) {
        onPostDestroyed?.invoke(activity)
    }
}


class ActivityLifecycleCallbackBuilder internal constructor() {
    private var onPreCreated: OnActivityPreCreatedCallback? = null
    private var onCreated: OnActivityCreatedCallback? = null
    private var onPostCreated: OnActivityPostCreatedCallback? = null
    private var onPreStarted: OnActivityPreStartedCallback? = null
    private var onStarted: OnActivityStartedCallback? = null
    private var onPostStarted: OnActivityPostStartedCallback? = null
    private var onPreResumed: OnActivityPreResumedCallback? = null
    private var onResumed: OnActivityResumedCallback? = null
    private var onPostResumed: OnActivityPostResumedCallback? = null
    private var onPrePaused: OnActivityPrePausedCallback? = null
    private var onPaused: OnActivityPausedCallback? = null
    private var onPostPaused: OnActivityPostPausedCallback? = null
    private var onPreStopped: OnActivityPreStoppedCallback? = null
    private var onStopped: OnActivityStoppedCallback? = null
    private var onPostStopped: OnActivityPostStoppedCallback? = null
    private var onPreSaveInstanceState: OnActivityPreSaveInstanceStateCallback? = null
    private var onSaveInstanceState: OnActivitySaveInstanceStateCallback? = null
    private var onPostSaveInstanceState: OnActivityPostSaveInstanceStateCallback? = null
    private var onPreDestroyed: OnActivityPreDestroyedCallback? = null
    private var onDestroyed: OnActivityDestroyedCallback? = null
    private var onPostDestroyed: OnActivityPostDestroyedCallback? = null

    @JvmSynthetic
    fun onActivityPreCreated(block: OnActivityPreCreatedCallback) {
        onPreCreated = block
    }

    @JvmSynthetic
    fun onActivityCreated(block: OnActivityCreatedCallback) {
        onCreated = block
    }

    @JvmSynthetic
    fun onActivityPostCreated(block: OnActivityPostCreatedCallback) {
        onPostCreated = block
    }

    @JvmSynthetic
    fun onActivityPreStarted(block: OnActivityPreStartedCallback) {
        onPreStarted = block
    }

    @JvmSynthetic
    fun onActivityStarted(block: OnActivityStartedCallback) {
        onStarted = block
    }

    @JvmSynthetic
    fun onActivityPostStarted(block: OnActivityPostStartedCallback) {
        onPostStarted = block
    }

    @JvmSynthetic
    fun onActivityPreResumed(block: OnActivityPreResumedCallback) {
        onPreResumed = block
    }

    @JvmSynthetic
    fun onActivityResumed(block: OnActivityResumedCallback) {
        onResumed = block
    }

    @JvmSynthetic
    fun onActivityPostResumed(block: OnActivityPostResumedCallback) {
        onPostResumed = block
    }

    @JvmSynthetic
    fun onActivityPrePaused(block: OnActivityPrePausedCallback) {
        onPrePaused = block
    }

    @JvmSynthetic
    fun onActivityPaused(block: OnActivityPausedCallback) {
        onPaused = block
    }

    @JvmSynthetic
    fun onActivityPostPaused(block: OnActivityPostPausedCallback) {
        onPostPaused = block
    }

    @JvmSynthetic
    fun onActivityPreStopped(block: OnActivityPreStoppedCallback) {
        onPreStopped = block
    }

    @JvmSynthetic
    fun onActivityStopped(block: OnActivityStoppedCallback) {
        onStopped = block
    }

    @JvmSynthetic
    fun onActivityPostStopped(block: OnActivityPostStoppedCallback) {
        onPostStopped = block
    }

    @JvmSynthetic
    fun onActivityPreSaveInstanceState(block: OnActivityPreSaveInstanceStateCallback) {
        onPreSaveInstanceState = block
    }

    @JvmSynthetic
    fun onActivitySaveInstanceState(block: OnActivitySaveInstanceStateCallback) {
        onSaveInstanceState = block
    }

    @JvmSynthetic
    fun onActivityPostSaveInstanceState(block: OnActivityPostSaveInstanceStateCallback) {
        onPostSaveInstanceState = block
    }

    @JvmSynthetic
    fun onActivityPreDestroyed(block: OnActivityPreDestroyedCallback) {
        onPreDestroyed = block
    }

    @JvmSynthetic
    fun onActivityDestroyed(block: OnActivityDestroyedCallback) {
        onDestroyed = block
    }

    @JvmSynthetic
    fun onActivityPostDestroyed(block: OnActivityPostDestroyedCallback) {
        onPostDestroyed = block
    }

    @JvmSynthetic
    fun build()=ActivityLifecycleCallbacks(
        onPreCreated=onPreCreated,
        onCreated=onCreated,
        onPostCreated=onPostCreated,
        onPreStarted=onPreStarted,
        onStarted=onStarted,
        onPostStarted=onPostStarted,
        onPreResumed=onPreResumed,
        onResumed=onResumed,
        onPostResumed=onPostResumed,
        onPrePaused=onPrePaused,
        onPaused=onPaused,
        onPostPaused=onPostPaused,
        onPreStopped=onPreStopped,
        onStopped=onStopped,
        onPostStopped=onPostStopped,
        onPreSaveInstanceState=onPreSaveInstanceState,
        onSaveInstanceState=onSaveInstanceState,
        onPostSaveInstanceState=onPostSaveInstanceState,
        onPreDestroyed=onPreDestroyed,
        onDestroyed=onDestroyed,
        onPostDestroyed=onPostDestroyed
    )
}

@JvmSynthetic
fun activityLifecycleCallbacks(block:ActivityLifecycleCallbackBuilder.() -> Unit) =
    ActivityLifecycleCallbackBuilder().apply(block).build()
