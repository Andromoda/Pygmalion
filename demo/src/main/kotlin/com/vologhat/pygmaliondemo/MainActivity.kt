package com.vologhat.pygmaliondemo

import android.os.Bundle
import android.view.ContextThemeWrapper
import androidx.appcompat.app.AppCompatActivity
import com.vologhat.pygmalion.Pygmalion
import com.vologhat.pygmalion.inflater.factory2Hook
import com.vologhat.pygmaliondemo.databinding.ActivityMainBinding

class MainActivity:AppCompatActivity()
{
    private lateinit var binding:ActivityMainBinding
    
    override fun onCreate(savedInstanceState:Bundle?)
    {
        super.onCreate(savedInstanceState)

        val factory2=Pygmalion.attachToLayoutInflater(layoutInflater)
        factory2.registerHook(
            factory2Hook {
                onCreateView { name,context,attrs ->
                    when
                    {
                        name.endsWith("AppCompatTextView") -> {
                            DemoTextView(context,attrs)//inflate own TextView
                        }
                        else -> null
                    }
                }
            },
            MainActivity::class.java,ContextThemeWrapper::class.java
        )

        binding=ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        
        binding.sampleText.apply {
            text=this::class.java.simpleName//print text view simple class to check factory2 hooking
            setTextColor(resources.getColor(R.color.black))
        }
    }
}