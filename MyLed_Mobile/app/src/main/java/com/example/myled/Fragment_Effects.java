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

public class Fragment_Effects extends Fragment {
    ConstraintLayout effects_layout;
    ImageView effects_bg;
    TextView tV_off_effect,
            tV_effects,
            tV_speedEffect,
            tV_effect_RainbowLoop,
            tV_effect_FlipFlop,
            tV_effect_Fade,
            tV_effect_Rainbow,
            tV_effect_RainbowFade,
            tV_effect_RandomColorFade,
            tV_effect_Police;
    SeekBar effect_delay_seekBar;
    ImageButton iB_effect_off,
            iB_effect_RainbowLoop,
            iB_effect_FlipFlop,
            iB_effect_Fade,
            iB_effect_Rainbow,
            iB_effect_RainbowFade,
            iB_effect_RandomColorFade,
            iB_effect_Police;


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment__effects, container, false);

        iB_effect_off = view.findViewById(R.id.iB_colorMusic_off);
        iB_effect_RainbowLoop = view.findViewById(R.id.iB_effect_RainbowLoop);
        iB_effect_FlipFlop = view.findViewById(R.id.iB_effect_FlipFlop);
        iB_effect_Fade = view.findViewById(R.id.iB_effect_Fade);
        iB_effect_Rainbow = view.findViewById(R.id.iB_effect_Rainbow);
        iB_effect_RainbowFade = view.findViewById(R.id.iB_effect_RainbowFade);
        iB_effect_RandomColorFade = view.findViewById(R.id.iB_effect_RandomColorFade);
        iB_effect_Police = view.findViewById(R.id.iB_effect_Police);

        effect_delay_seekBar = view.findViewById(R.id.effect_delay_seekBar);

        effects_bg = view.findViewById(R.id.effects_bg);

        tV_effects = view.findViewById(R.id.tV_effects);
        tV_off_effect = view.findViewById(R.id.tV_off_effect);
        tV_speedEffect = view.findViewById(R.id.tV_speedEffect);
        tV_effect_RainbowLoop = view.findViewById(R.id.tV_effect_RainbowLoop);
        tV_effect_FlipFlop = view.findViewById(R.id.tV_effect_FlipFlop);
        tV_effect_Fade = view.findViewById(R.id.tV_effect_Fade);
        tV_effect_Rainbow = view.findViewById(R.id.tV_effect_Rainbow);
        tV_effect_RainbowFade = view.findViewById(R.id.tV_effect_RainbowFade);
        tV_effect_RandomColorFade = view.findViewById(R.id.tV_effect_RandomColorFade);
        tV_effect_Police = view.findViewById(R.id.tV_effect_Police);

        effects_layout = view.findViewById(R.id.effects_layout);

        if(Memory.theme == 0){
            effects_layout.setBackgroundColor(getResources().getColor(R.color.dark));
            effects_bg.setImageDrawable(getResources().getDrawable(R.drawable.scroll_bg));
            effect_delay_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb));
            effect_delay_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar));

            tV_effects.setTextColor(getResources().getColor(R.color.grey));
            tV_speedEffect.setTextColor(getResources().getColor(R.color.grey));
            tV_effect_RainbowLoop.setTextColor(getResources().getColor(R.color.grey));
            tV_effect_FlipFlop.setTextColor(getResources().getColor(R.color.grey));
            tV_effect_Fade.setTextColor(getResources().getColor(R.color.grey));
            tV_effect_Rainbow.setTextColor(getResources().getColor(R.color.grey));
            tV_effect_RainbowFade.setTextColor(getResources().getColor(R.color.grey));
            tV_effect_RandomColorFade.setTextColor(getResources().getColor(R.color.grey));
            tV_effect_Police.setTextColor(getResources().getColor(R.color.grey));

            iB_effect_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_button));
            iB_effect_RainbowLoop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
            iB_effect_FlipFlop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
            iB_effect_Fade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
            iB_effect_Rainbow.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
            iB_effect_RainbowFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
            iB_effect_RandomColorFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
            iB_effect_Police.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
        }else{
            effects_layout.setBackgroundColor(getResources().getColor(R.color.light));
            effects_bg.setImageDrawable(getResources().getDrawable(R.drawable.scroll_bg_white));
            effect_delay_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb_white));
            effect_delay_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar_white));

            tV_effects.setTextColor(getResources().getColor(R.color.grey_light));
            tV_speedEffect.setTextColor(getResources().getColor(R.color.grey_light));
            tV_effect_RainbowLoop.setTextColor(getResources().getColor(R.color.grey_light));
            tV_effect_FlipFlop.setTextColor(getResources().getColor(R.color.grey_light));
            tV_effect_Fade.setTextColor(getResources().getColor(R.color.grey_light));
            tV_effect_Rainbow.setTextColor(getResources().getColor(R.color.grey_light));
            tV_effect_RainbowFade.setTextColor(getResources().getColor(R.color.grey_light));
            tV_effect_RandomColorFade.setTextColor(getResources().getColor(R.color.grey_light));
            tV_effect_Police.setTextColor(getResources().getColor(R.color.grey_light));

            iB_effect_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_button_white));
            iB_effect_RainbowLoop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
            iB_effect_FlipFlop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
            iB_effect_Fade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
            iB_effect_Rainbow.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
            iB_effect_RainbowFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
            iB_effect_RandomColorFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
            iB_effect_Police.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
        }



        iB_effect_off.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if(motionEvent.getAction() == MotionEvent.ACTION_DOWN){
                    if(Memory.theme == 0) {
                        iB_effect_RainbowLoop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                        iB_effect_FlipFlop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                        iB_effect_Fade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                        iB_effect_Rainbow.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                        iB_effect_RainbowFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                        iB_effect_RandomColorFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                        iB_effect_Police.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));

                        iB_effect_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_button));
                    }else{
                        iB_effect_RainbowLoop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                        iB_effect_FlipFlop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                        iB_effect_Fade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                        iB_effect_Rainbow.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                        iB_effect_RainbowFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                        iB_effect_RandomColorFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                        iB_effect_Police.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));

                        iB_effect_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_button_white));
                    }

                    byte[] tx_data = new byte[2];
                    Memory.effect = 0;
                    tx_data[0] = Commands.SET_EFFECT;
                    tx_data[1] = (byte)Memory.effect;
                    DataSender ds = new DataSender();
                    ds.execute(tx_data);
                } else if(motionEvent.getAction() == MotionEvent.ACTION_UP){
                    if(Memory.theme == 0) {
                        iB_effect_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_button));
                        tV_off_effect.setText(getResources().getText(R.string.off));
                        tV_off_effect.setTextColor(getResources().getColor(R.color.grey));
                    }else{
                        iB_effect_off.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_button_white));
                        tV_off_effect.setText(getResources().getText(R.string.off));
                        tV_off_effect.setTextColor(getResources().getColor(R.color.grey_light));
                    }
                }
                return false;
            }
        });

        View.OnClickListener effectClick = new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                if(Memory.theme == 0) {
                    iB_effect_RainbowLoop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                    iB_effect_FlipFlop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                    iB_effect_Fade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                    iB_effect_Rainbow.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                    iB_effect_RainbowFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                    iB_effect_RandomColorFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));
                    iB_effect_Police.setImageDrawable(getResources().getDrawable(R.drawable.effect_off));

                    ((ImageButton) v).setImageDrawable(getResources().getDrawable(R.drawable.effect_on));

                    tV_off_effect.setText(getResources().getText(R.string.on));
                    tV_off_effect.setTextColor(getResources().getColor(R.color.orange));
                }else{
                    iB_effect_RainbowLoop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                    iB_effect_FlipFlop.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                    iB_effect_Fade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                    iB_effect_Rainbow.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                    iB_effect_RainbowFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                    iB_effect_RandomColorFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));
                    iB_effect_Police.setImageDrawable(getResources().getDrawable(R.drawable.effect_off_white));

                    ((ImageButton) v).setImageDrawable(getResources().getDrawable(R.drawable.effect_on_white));

                    tV_off_effect.setText(getResources().getText(R.string.on));
                    tV_off_effect.setTextColor(getResources().getColor(R.color.orange_light));
                }

                byte[] tx_data = new byte[2];
                Memory.effect = Integer.parseInt(v.getTag().toString());
                Memory.color_music = 0;
                tx_data[0] = Commands.SET_EFFECT;
                tx_data[1] = (byte)Memory.effect;
                DataSender ds = new DataSender();
                ds.execute(tx_data);
            }
        };


        SeekBar.OnSeekBarChangeListener seekChange = new SeekBar.OnSeekBarChangeListener(){
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                if(seekBar == effect_delay_seekBar) {
                    Memory.effect_delay = effect_delay_seekBar.getProgress();
                    byte[] tx_data = new byte[2];
                    tx_data[0] = Commands.SET_EFFECT_DELAY;
                    tx_data[1] = (byte)(100 - effect_delay_seekBar.getProgress());
                    DataSender ds = new DataSender();
                    ds.execute(tx_data);
                }
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {}
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {}
        };

        effect_delay_seekBar.setProgress(Memory.effect_delay);
        if(Memory.effect == 0){
            tV_off_effect.setText(getResources().getText(R.string.off));
            if(Memory.theme == 0)
                tV_off_effect.setTextColor(getResources().getColor(R.color.grey));
            else tV_off_effect.setTextColor(getResources().getColor(R.color.grey_light));
        }else if(Memory.effect != 0 && Memory.color_music == 0){
            tV_off_effect.setText(getResources().getText(R.string.on));
            if(Memory.theme == 0)
                tV_off_effect.setTextColor(getResources().getColor(R.color.orange));
            else tV_off_effect.setTextColor(getResources().getColor(R.color.orange_light));
        }

        if(Memory.theme == 0) {
            if (Integer.parseInt(iB_effect_RainbowLoop.getTag().toString()) == Memory.effect) {
                iB_effect_RainbowLoop.setImageDrawable(getResources().getDrawable(R.drawable.effect_on));
            } else if (Integer.parseInt(iB_effect_FlipFlop.getTag().toString()) == Memory.effect) {
                iB_effect_FlipFlop.setImageDrawable(getResources().getDrawable(R.drawable.effect_on));
            } else if (Integer.parseInt(iB_effect_Fade.getTag().toString()) == Memory.effect) {
                iB_effect_Fade.setImageDrawable(getResources().getDrawable(R.drawable.effect_on));
            } else if (Integer.parseInt(iB_effect_Rainbow.getTag().toString()) == Memory.effect) {
                iB_effect_Rainbow.setImageDrawable(getResources().getDrawable(R.drawable.effect_on));
            } else if (Integer.parseInt(iB_effect_RainbowFade.getTag().toString()) == Memory.effect) {
                iB_effect_RainbowFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_on));
            } else if (Integer.parseInt(iB_effect_RandomColorFade.getTag().toString()) == Memory.effect) {
                iB_effect_RandomColorFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_on));
            } else if (Integer.parseInt(iB_effect_Police.getTag().toString()) == Memory.effect) {
                iB_effect_Police.setImageDrawable(getResources().getDrawable(R.drawable.effect_on));
            }
        } else{
            if (Integer.parseInt(iB_effect_RainbowLoop.getTag().toString()) == Memory.effect) {
                iB_effect_RainbowLoop.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_white));
            } else if (Integer.parseInt(iB_effect_FlipFlop.getTag().toString()) == Memory.effect) {
                iB_effect_FlipFlop.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_white));
            } else if (Integer.parseInt(iB_effect_Fade.getTag().toString()) == Memory.effect) {
                iB_effect_Fade.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_white));
            } else if (Integer.parseInt(iB_effect_Rainbow.getTag().toString()) == Memory.effect) {
                iB_effect_Rainbow.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_white));
            } else if (Integer.parseInt(iB_effect_RainbowFade.getTag().toString()) == Memory.effect) {
                iB_effect_RainbowFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_white));
            } else if (Integer.parseInt(iB_effect_RandomColorFade.getTag().toString()) == Memory.effect) {
                iB_effect_RandomColorFade.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_white));
            } else if (Integer.parseInt(iB_effect_Police.getTag().toString()) == Memory.effect) {
                iB_effect_Police.setImageDrawable(getResources().getDrawable(R.drawable.effect_on_white));
            }
        }

        iB_effect_RainbowLoop.setOnClickListener(effectClick);
        iB_effect_FlipFlop.setOnClickListener(effectClick);
        iB_effect_Fade.setOnClickListener(effectClick);
        iB_effect_Rainbow.setOnClickListener(effectClick);
        iB_effect_RainbowFade.setOnClickListener(effectClick);
        iB_effect_RandomColorFade.setOnClickListener(effectClick);
        iB_effect_Police.setOnClickListener(effectClick);

        effect_delay_seekBar.setOnSeekBarChangeListener(seekChange);

        return view;
    }
}