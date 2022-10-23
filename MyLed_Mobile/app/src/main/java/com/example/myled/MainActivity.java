package com.example.myled;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.fragment.app.FragmentTransaction;

import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.DisplayCutout;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    SharedPreferences myPreferences;
    ImageButton iB_Home, iB_Effects, iB_ColorMusic, iB_Settings;
    TextView tV_Home, tV_Effects, tV_ColorMusic, tV_Settings;
    ConstraintLayout activity_layout, instruction_layout;

    private void loadSavedSettings(){
        myPreferences = getPreferences(MODE_PRIVATE);
        Memory.brightness = myPreferences.getInt("brightness", 0);
        Memory.color_r = myPreferences.getInt("color_r", 0);
        Memory.color_g = myPreferences.getInt("color_g", 0);
        Memory.color_b = myPreferences.getInt("color_b", 0);
        Memory.effect = myPreferences.getInt("effect", 0);
        Memory.effect_delay = myPreferences.getInt("effect_delay", 0);
        Memory.l_sens = myPreferences.getInt("l_sens", 0);
        Memory.m_sens = myPreferences.getInt("m_sens", 0);
        Memory.h_sens = myPreferences.getInt("h_sens", 0);
        Memory.color_music = myPreferences.getInt("color_music", 0);
        Memory.color_music_delay = myPreferences.getInt("color_music_delay", 0);
        Memory.theme = myPreferences.getInt("theme", 0);
    }

    private void saveSettings(){
        myPreferences = getPreferences(MODE_PRIVATE);
        SharedPreferences.Editor ed = myPreferences.edit();
        ed.putInt("brightness", Memory.brightness);
        ed.putInt("color_r", Memory.color_r);
        ed.putInt("color_g", Memory.color_g);
        ed.putInt("color_b", Memory.color_b);
        ed.putInt("effect", Memory.effect);
        ed.putInt("effect_delay", Memory.effect_delay);
        ed.putInt("l_sens", Memory.l_sens);
        ed.putInt("m_sens", Memory.m_sens);
        ed.putInt("h_sens", Memory.h_sens);
        ed.putInt("color_music", Memory.color_music);
        ed.putInt("color_music_delay", Memory.color_music_delay);
        ed.putInt("theme", Memory.theme);
        ed.apply();
    }

    @Override
    protected void onStop() {
        super.onStop();
        saveSettings();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
        setContentView(R.layout.activity_main);

        iB_Home = findViewById(R.id.iB_Home);
        iB_Effects = findViewById(R.id.iB_Effects);
        iB_ColorMusic = findViewById(R.id.iB_ColorMusic);
        iB_Settings = findViewById(R.id.iB_Settings);
        tV_Home = findViewById(R.id.tV_Home);
        tV_Effects = findViewById(R.id.tV_Effects);
        tV_ColorMusic = findViewById(R.id.tV_ColorMusic);
        tV_Settings = findViewById(R.id.tV_Settings);
        activity_layout = findViewById(R.id.activity_layout);
        instruction_layout = findViewById(R.id.instruction_layout);

        instruction_layout.setVisibility(View.INVISIBLE);
        loadSavedSettings();

        if(Memory.theme == 0) {
            getWindow().setStatusBarColor(getResources().getColor(R.color.dark));
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            tV_Home.setTextColor(getResources().getColor(R.color.grey));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey));
            activity_layout.setBackgroundColor(getResources().getColor(R.color.dark));
        }else{
            getWindow().setStatusBarColor(getResources().getColor(R.color.light));
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on_white));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            tV_Home.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey_light));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey_light));
            activity_layout.setBackgroundColor(getResources().getColor(R.color.light));
        }
        Fragment_Main fm = new Fragment_Main();
        FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
        ft.replace(R.id.container, fm);
        ft.commit();
    }

    public void gotoHome(View v){
        if(Memory.theme == 0) {
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            tV_Home.setTextColor(getResources().getColor(R.color.grey));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey));
        }else{
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on_white));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            tV_Home.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey_light));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey_light));
        }
        Fragment_Main fm = new Fragment_Main();
        FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
        ft.replace(R.id.container, fm);
        ft.commit();
    }
    public void gotoEffects(View v){
        if(Memory.theme == 0) {
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            tV_Home.setTextColor(getResources().getColor(R.color.grey));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey));
        }else{
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on_white));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            tV_Home.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey_light));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey_light));
        }
        Fragment_Effects fe = new Fragment_Effects();
        FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
        ft.replace(R.id.container, fe);
        ft.commit();
    }
    public void gotoColorMusic(View v){
        if(Memory.theme == 0) {
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            tV_Home.setTextColor(getResources().getColor(R.color.grey));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey));
        }else{
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on_white));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            tV_Home.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey_light));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey_light));
        }
        Fragment_ColorMusic fcm = new Fragment_ColorMusic();
        FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
        ft.replace(R.id.container, fcm);
        ft.commit();
    }
    public void gotoSettints(View v){
        if(Memory.theme == 0) {
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on));
            tV_Home.setTextColor(getResources().getColor(R.color.grey));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey));
        }else{
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on_white));
            tV_Home.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey_light));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey_light));
        }
        Fragment_Settings fs = new Fragment_Settings();
        FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
        ft.replace(R.id.container, fs);
        ft.commit();
    }
}