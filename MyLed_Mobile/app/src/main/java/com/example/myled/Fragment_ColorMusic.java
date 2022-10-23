package com.example.myled;

import android.os.Bundle;

import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;

public class Fragment_ColorMusic extends Fragment {
    ConstraintLayout colorMusic_layout;
    ImageView colorMusic_bg;
    TextView tV_off,
            tV_colorMusic,
            tV_cm_Sectros,
            tV_cm_RunningLeds,
            tV_cm_Flashing,
            tV_cm_speed,
            tV_sensetive,
            tV_bass,
            tV_middle,
            tV_treble;
    SeekBar l_sens_seekBar,
            m_sens_seekBar,
            h_sens_seekBar,
            color_music_delay_seekBar;
    ImageButton iB_colorMusic_off,
            iB_cm_Sectors,
            iB_cm_RunningLeds,
            iB_cm_Flashing;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment__color_music, container, false);

        l_sens_seekBar = view.findViewById(R.id.l_sens_seekBar);
        m_sens_seekBar = view.findViewById(R.id.m_sens_seekBar);
        h_sens_seekBar = view.findViewById(R.id.h_sens_seekBar);
        color_music_delay_seekBar = view.findViewById(R.id.color_music_delay_seekBar);

        iB_colorMusic_off = view.findViewById(R.id.iB_colorMusic_off);
        iB_cm_Sectors = view.findViewById(R.id.iB_cm_Sectors);
        iB_cm_RunningLeds = view.findViewById(R.id.iB_cm_RunningLeds);
        iB_cm_Flashing = view.findViewById(R.id.iB_cm_Flashing);

        tV_off = view.findViewById(R.id.tV_off_effect);
        tV_colorMusic  = view.findViewById(R.id.tV_colorMusic);
        tV_cm_Sectros = view.findViewById(R.id.tV_cm_Sectros);
        tV_cm_RunningLeds = view.findViewById(R.id.tV_cm_RunningLeds);
        tV_cm_Flashing = view.findViewById(R.id.tV_cm_Flashing);
        tV_cm_speed = view.findViewById(R.id.tV_cm_speed);
        tV_sensetive = view.findViewById(R.id.tV_sensetive);
        tV_bass = view.findViewById(R.id.tV_bass);
        tV_middle = view.findViewById(R.id.tV_middle);
        tV_treble = view.findViewById(R.id.tV_treble);

        colorMusic_layout = view.findViewById(R.id.colorMusic_layout);
        colorMusic_bg = view.findViewById(R.id.colorMusic_bg);

        if(Memory.theme == 0){
            colorMusic_layout.setBackgroundColor(getResources().getColor(R.color.dark));
            colorMusic_bg.setImageDrawable(getResources().getDrawable(R.drawable.color_music_bg));

            tV_cm_Sectros.setTextColor(getResources().getColor(R.color.grey));
            tV_cm_RunningLeds.setTextColor(getResources().getColor(R.color.grey));
            tV_cm_Flashing.setTextColor(getResources().getColor(R.color.grey));

            tV_colorMusic.setTextColor(getResources().getColor(R.color.grey));
            tV_cm_speed.setTextColor(getResources().getColor(R.color.grey));
            tV_sensetive.setTextColor(getResources().getColor(R.color.grey));
            tV_bass.setTextColor(getResources().getColor(R.color.grey));
            tV_middle.setTextColor(getResources().getColor(R.color.grey));
            tV_treble.setTextColor(getResources().getColor(R.color.grey));

            l_sens_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb));
            l_sens_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar));
            h_sens_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb));
            h_sens_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar));
            m_sens_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb));
            m_sens_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar));
            color_music_delay_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb));
            color_music_delay_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar));

            iB_colorMusic_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_button));
            iB_cm_Sectors.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off));
            iB_cm_RunningLeds.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off));
            iB_cm_Flashing.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off));
        }else{
            colorMusic_layout.setBackgroundColor(getResources().getColor(R.color.light));
            colorMusic_bg.setImageDrawable(getResources().getDrawable(R.drawable.color_music_bg_white));

            tV_cm_Sectros.setTextColor(getResources().getColor(R.color.grey_light));
            tV_cm_RunningLeds.setTextColor(getResources().getColor(R.color.grey_light));
            tV_cm_Flashing.setTextColor(getResources().getColor(R.color.grey_light));

            tV_colorMusic.setTextColor(getResources().getColor(R.color.grey_light));
            tV_cm_speed.setTextColor(getResources().getColor(R.color.grey_light));
            tV_sensetive.setTextColor(getResources().getColor(R.color.grey_light));
            tV_bass.setTextColor(getResources().getColor(R.color.grey_light));
            tV_middle.setTextColor(getResources().getColor(R.color.grey_light));
            tV_treble.setTextColor(getResources().getColor(R.color.grey_light));

            l_sens_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb_white));
            l_sens_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar_white));
            h_sens_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb_white));
            h_sens_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar_white));
            m_sens_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb_white));
            m_sens_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar_white));
            color_music_delay_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb_white));
            color_music_delay_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar_white));

            iB_colorMusic_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_button_white));
            iB_cm_Sectors.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off_white));
            iB_cm_RunningLeds.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off_white));
            iB_cm_Flashing.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off_white));
        }



        iB_colorMusic_off.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if(motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    if (Memory.theme == 0) {
                        iB_cm_Sectors.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off));
                        iB_cm_RunningLeds.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off));
                        iB_cm_Flashing.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off));

                        iB_colorMusic_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_button));
                    }else{
                        iB_cm_Sectors.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off_white));
                        iB_cm_RunningLeds.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off_white));
                        iB_cm_Flashing.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off_white));

                        iB_colorMusic_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_button_white));
                    }


                    byte[] tx_data = new byte[2];
                    Memory.color_music = 0;
                    tx_data[0] = Commands.SET_COLOR_MUSIC;
                    tx_data[1] = (byte)Memory.color_music;
                    DataSender ds = new DataSender();
                    ds.execute(tx_data);
                } else if(motionEvent.getAction() == MotionEvent.ACTION_UP){
                    if(Memory.theme == 0){
                        iB_colorMusic_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_button));
                        tV_off.setTextColor(getResources().getColor(R.color.grey));
                    }else{
                        iB_colorMusic_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_button_white));
                        tV_off.setTextColor(getResources().getColor(R.color.grey_light));
                    }
                    tV_off.setText(getResources().getString(R.string.off));
                }
                return false;
            }
        });

        View.OnClickListener cmClick = new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                if(Memory.theme == 0){
                    iB_cm_Sectors.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off));
                    iB_cm_RunningLeds.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off));
                    iB_cm_Flashing.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off));

                    ((ImageButton)v).setImageDrawable(getResources().getDrawable(R.drawable.colormusic_on));

                    tV_off.setTextColor(getResources().getColor(R.color.orange));
                }else{
                    iB_cm_Sectors.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off_white));
                    iB_cm_RunningLeds.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off_white));
                    iB_cm_Flashing.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_off_white));

                    ((ImageButton)v).setImageDrawable(getResources().getDrawable(R.drawable.colormusic_on_white));

                    tV_off.setTextColor(getResources().getColor(R.color.orange_light));
                }

                tV_off.setText(getResources().getString(R.string.on));

                byte[] tx_data = new byte[2];
                Memory.color_music = Integer.parseInt(v.getTag().toString());
                Memory.effect = 0;
                tx_data[0] = Commands.SET_COLOR_MUSIC;
                tx_data[1] = (byte)Memory.color_music;
                DataSender ds = new DataSender();
                ds.execute(tx_data);
            }
        };

        SeekBar.OnSeekBarChangeListener seekChange = new SeekBar.OnSeekBarChangeListener(){
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                if(seekBar == l_sens_seekBar || seekBar == m_sens_seekBar || seekBar == h_sens_seekBar){
                    Memory.l_sens = l_sens_seekBar.getProgress();
                    Memory.m_sens = m_sens_seekBar.getProgress();
                    Memory.h_sens = h_sens_seekBar.getProgress();
                    byte[] tx_data = new byte[4];
                    tx_data[0] = Commands.SET_COLOR_MUSIC_SENSIVITY;
                    tx_data[1] = (byte)(100 - l_sens_seekBar.getProgress());
                    tx_data[2] = (byte)(100 - m_sens_seekBar.getProgress());
                    tx_data[3] = (byte)(100 - h_sens_seekBar.getProgress());
                    DataSender ds = new DataSender();
                    ds.execute(tx_data);
                }
                if(seekBar == color_music_delay_seekBar){
                    Memory.color_music_delay = color_music_delay_seekBar.getProgress();
                    byte[] tx_data = new byte[2];
                    tx_data[0] = Commands.SET_COLOR_MUSIC_DELAY;
                    tx_data[1] = (byte)(100 - color_music_delay_seekBar.getProgress());
                    DataSender ds = new DataSender();
                    ds.execute(tx_data);
                }
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {}
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {}
        };


        l_sens_seekBar.setProgress(Memory.l_sens);
        m_sens_seekBar.setProgress(Memory.m_sens);
        h_sens_seekBar.setProgress(Memory.h_sens);
        color_music_delay_seekBar.setProgress(Memory.color_music_delay);
        if(Memory.color_music == 0){
            if(Memory.theme == 0)
                tV_off.setTextColor(getResources().getColor(R.color.grey));
            else
                tV_off.setTextColor(getResources().getColor(R.color.grey_light));
            tV_off.setText(getResources().getString(R.string.off));
        }else if(Memory.color_music != 0 && Memory.effect == 0){
            if(Memory.theme == 0)
                tV_off.setTextColor(getResources().getColor(R.color.orange));
            else
                tV_off.setTextColor(getResources().getColor(R.color.orange_light));
            tV_off.setText(getResources().getString(R.string.on));
        }

        if(Memory.theme == 0) {
            if (Integer.parseInt(iB_cm_Sectors.getTag().toString()) == Memory.color_music) {
                iB_cm_Sectors.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_on));
            } else if (Integer.parseInt(iB_cm_RunningLeds.getTag().toString()) == Memory.color_music) {
                iB_cm_RunningLeds.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_on));
            } else if (Integer.parseInt(iB_cm_Flashing.getTag().toString()) == Memory.color_music) {
                iB_cm_Flashing.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_on));
            }
        }else{
            if (Integer.parseInt(iB_cm_Sectors.getTag().toString()) == Memory.color_music) {
                iB_cm_Sectors.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_on_white));
            } else if (Integer.parseInt(iB_cm_RunningLeds.getTag().toString()) == Memory.color_music) {
                iB_cm_RunningLeds.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_on_white));
            } else if (Integer.parseInt(iB_cm_Flashing.getTag().toString()) == Memory.color_music) {
                iB_cm_Flashing.setImageDrawable(getResources().getDrawable(R.drawable.colormusic_on_white));
            }
        }

        l_sens_seekBar.setOnSeekBarChangeListener(seekChange);
        m_sens_seekBar.setOnSeekBarChangeListener(seekChange);
        h_sens_seekBar.setOnSeekBarChangeListener(seekChange);
        color_music_delay_seekBar.setOnSeekBarChangeListener(seekChange);

        iB_cm_Sectors.setOnClickListener(cmClick);
        iB_cm_RunningLeds.setOnClickListener(cmClick);
        iB_cm_Flashing.setOnClickListener(cmClick);

        return view;
    }
}