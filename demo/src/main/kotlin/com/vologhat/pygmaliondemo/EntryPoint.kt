package com.vologhat.pygmaliondemo

import android.app.Application
import android.nfc.Tag
import android.util.Log
import com.vologhat.pygmalion.Pygmalion
import com.vologhat.pygmalion.hooks.assetHook

class EntryPoint
    :Application()
{
    override fun onCreate()
    {
        super.onCreate()
        
        //initialize pygmalion
        Pygmalion.initialize()
        //check if pygmalion is initialized
        Log.d("Pygmalion","${Pygmalion.isInitialized()}")
        if(Pygmalion.isInitialized())
        {
            //get original resource value before hooking
            val teal200=Pygmalion.getValue(R.color.teal_200)
            
            //enable hooking
            Pygmalion.hook()
            
            //register AssetManager hook
            Pygmalion.registerAssetHooks(
                assetHook {
                    onApplyStyle { assets ->
                        assets.inAttrs.forEachIndexed { index,attr ->
                            val outValue=assets.outValues[index]
                            when
                            {
                                attr==com.google.android.material.R.attr.colorPrimary ->
                                    outValue.setTo(teal200)
                                
                                attr==android.R.attr.statusBarColor ->
                                    outValue.setTo(teal200)
                                
                                attr==android.R.attr.navigationBarColor ->
                                    Pygmalion.getValue(R.color.purple_200,true,outValue=outValue)
                                
                                attr==android.R.attr.windowBackground ->
                                    Pygmalion.getValue(
                                        android.R.color.holo_red_dark,
                                        true,
                                        Pygmalion.systemResources,
                                        outValue
                                    )
                                
                                attr==android.R.attr.tint ->
                                    Pygmalion.getValue(
                                        android.R.color.holo_green_dark,
                                        true,
                                        Pygmalion.systemResources,
                                        outValue
                                    )
                                
                                attr==android.R.attr.colorAccent ->
                                    Pygmalion.getValue(R.color.purple_700,true,outValue=outValue)
                            }
                        }
                    }
                }
            )
        }
    }
}