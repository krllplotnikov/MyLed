package com.example.myled;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;

import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

public class Fragment_Settings extends Fragment {
    MainActivity mainActivity;
    ConstraintLayout settings_layout, activity_layout, instruction_layout;
    EditText ssid_field,
            pass_field,
            ssidAP_field,
            passAP_field,
            numleds_field;
    ImageButton iB_submitRouter,
            iB_submitController,
            iB_submitNumleds,
            iB_theme,
            iB_instruction,

            iB_Home,
            iB_Effects,
            iB_ColorMusic,
            iB_Settings,

            iB_close;
    TextView tV_settings,
            tV_numled,
            tV_theme,
            tV_submitNumleds,
            tV_router,
            tV_ssid,
            tV_pass,
            tV_ssidAP,
            tV_passAP,
            tV_submitRouter,
            tV_controller,
            tV_submitController,
            tV_dark,
            tV_question,

            tV_Home,
            tV_Effects,
            tV_ColorMusic,
            tV_Settings,

            tV_instruction;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment__settings, container, false);

        numleds_field = view.findViewById(R.id.numleds_field);
        ssid_field = view.findViewById(R.id.ssid_field);
        pass_field = view.findViewById(R.id.pass_field);
        ssidAP_field = view.findViewById(R.id.ssidAP_field);
        passAP_field = view.findViewById(R.id.passAP_field);
        iB_submitRouter = view.findViewById(R.id.iB_submitRouter);
        iB_submitController = view.findViewById(R.id.iB_submitController);
        iB_submitNumleds = view.findViewById(R.id.iB_submitNumleds);
        iB_theme = view.findViewById(R.id.iB_theme);
        iB_instruction = view.findViewById(R.id.iB_instruction);

        tV_settings = view.findViewById(R.id.tV_settings);
        tV_numled = view.findViewById(R.id.tV_numled);
        tV_theme = view.findViewById(R.id.tV_theme);
        tV_submitNumleds = view.findViewById(R.id.tV_submitNumleds);
        tV_router = view.findViewById(R.id.tV_router);
        tV_ssid = view.findViewById(R.id.tV_ssid);
        tV_pass = view.findViewById(R.id.tV_pass);
        tV_ssidAP = view.findViewById(R.id.tV_ssidAP);
        tV_passAP = view.findViewById(R.id.tV_passAP);
        tV_submitRouter = view.findViewById(R.id.tV_submitRouter);
        tV_controller = view.findViewById(R.id.tV_controller);
        tV_submitController = view.findViewById(R.id.tV_submitController);
        tV_dark = view.findViewById(R.id.tV_dark);
        tV_question = view.findViewById(R.id.tV_question);


        settings_layout = view.findViewById(R.id.settings_layout);

        activity_layout = getActivity().findViewById(R.id.activity_layout);
        instruction_layout = getActivity().findViewById(R.id.instruction_layout);
        iB_Home = getActivity().findViewById(R.id.iB_Home);
        iB_Effects = getActivity().findViewById(R.id.iB_Effects);
        iB_ColorMusic = getActivity().findViewById(R.id.iB_ColorMusic);
        iB_Settings = getActivity().findViewById(R.id.iB_Settings);
        tV_Home = getActivity().findViewById(R.id.tV_Home);
        tV_Effects = getActivity().findViewById(R.id.tV_Effects);
        tV_ColorMusic = getActivity().findViewById(R.id.tV_ColorMusic);
        tV_Settings = getActivity().findViewById(R.id.tV_Settings);

        tV_instruction = getActivity().findViewById(R.id.tV_instruction);
        iB_close = getActivity().findViewById(R.id.iB_close);

        instruction_layout.setVisibility(View.INVISIBLE);

        if(Memory.theme == 0) {
            tV_settings.setTextColor(getResources().getColor(R.color.grey));
            tV_numled.setTextColor(getResources().getColor(R.color.grey));
            tV_theme.setTextColor(getResources().getColor(R.color.grey));
            tV_submitNumleds.setTextColor(getResources().getColor(R.color.grey));
            tV_router.setTextColor(getResources().getColor(R.color.grey));
            tV_ssid.setTextColor(getResources().getColor(R.color.grey));
            tV_pass.setTextColor(getResources().getColor(R.color.grey));
            tV_ssidAP.setTextColor(getResources().getColor(R.color.grey));
            tV_passAP.setTextColor(getResources().getColor(R.color.grey));
            tV_submitRouter.setTextColor(getResources().getColor(R.color.grey));
            tV_controller.setTextColor(getResources().getColor(R.color.grey));
            tV_submitController.setTextColor(getResources().getColor(R.color.grey));
            tV_dark.setTextColor(getResources().getColor(R.color.grey));
            tV_dark.setText(getResources().getString(R.string.dark));
            tV_instruction.setTextColor(getResources().getColor(R.color.grey));
            tV_question.setTextColor(getResources().getColor(R.color.grey));

            iB_submitRouter.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
            iB_submitController.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
            iB_submitNumleds.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
            iB_theme.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
            iB_instruction.setImageDrawable(getResources().getDrawable(R.drawable.about_button));

            ssid_field.setBackground(getResources().getDrawable(R.drawable.net_field));
            ssid_field.setTextColor(getResources().getColor(R.color.grey));
            pass_field.setBackground(getResources().getDrawable(R.drawable.net_field));
            pass_field.setTextColor(getResources().getColor(R.color.grey));
            ssidAP_field.setBackground(getResources().getDrawable(R.drawable.net_field));
            ssidAP_field.setTextColor(getResources().getColor(R.color.grey));
            passAP_field.setBackground(getResources().getDrawable(R.drawable.net_field));
            passAP_field.setTextColor(getResources().getColor(R.color.grey));
            numleds_field.setBackground(getResources().getDrawable(R.drawable.net_field));
            numleds_field.setTextColor(getResources().getColor(R.color.grey));

            settings_layout.setBackgroundColor(getResources().getColor(R.color.dark));
            activity_layout.setBackgroundColor(getResources().getColor(R.color.dark));
            instruction_layout.setBackgroundColor(getResources().getColor(R.color.dark_a));
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on));
            tV_Home.setTextColor(getResources().getColor(R.color.grey));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey));
            iB_close.setImageDrawable(getResources().getDrawable(R.drawable.close));

        } else{
            tV_settings.setTextColor(getResources().getColor(R.color.grey_light));
            tV_numled.setTextColor(getResources().getColor(R.color.grey_light));
            tV_theme.setTextColor(getResources().getColor(R.color.grey_light));
            tV_submitNumleds.setTextColor(getResources().getColor(R.color.grey_light));
            tV_router.setTextColor(getResources().getColor(R.color.grey_light));
            tV_ssid.setTextColor(getResources().getColor(R.color.grey_light));
            tV_pass.setTextColor(getResources().getColor(R.color.grey_light));
            tV_ssidAP.setTextColor(getResources().getColor(R.color.grey_light));
            tV_passAP.setTextColor(getResources().getColor(R.color.grey_light));
            tV_submitRouter.setTextColor(getResources().getColor(R.color.grey_light));
            tV_controller.setTextColor(getResources().getColor(R.color.grey_light));
            tV_submitController.setTextColor(getResources().getColor(R.color.grey_light));
            tV_dark.setTextColor(getResources().getColor(R.color.grey_light));
            tV_dark.setText(getResources().getString(R.string.light));
            tV_instruction.setTextColor(getResources().getColor(R.color.grey_light));
            tV_question.setTextColor(getResources().getColor(R.color.grey_light));

            iB_submitRouter.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
            iB_submitController.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
            iB_submitNumleds.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
            iB_theme.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
            iB_instruction.setImageDrawable(getResources().getDrawable(R.drawable.about_button_white));

            ssid_field.setBackground(getResources().getDrawable(R.drawable.net_field_white));
            ssid_field.setTextColor(getResources().getColor(R.color.grey_light));
            pass_field.setBackground(getResources().getDrawable(R.drawable.net_field_white));
            pass_field.setTextColor(getResources().getColor(R.color.grey_light));
            ssidAP_field.setBackground(getResources().getDrawable(R.drawable.net_field_white));
            ssidAP_field.setTextColor(getResources().getColor(R.color.grey_light));
            passAP_field.setBackground(getResources().getDrawable(R.drawable.net_field_white));
            passAP_field.setTextColor(getResources().getColor(R.color.grey_light));
            numleds_field.setBackground(getResources().getDrawable(R.drawable.numled_field_white));
            numleds_field.setTextColor(getResources().getColor(R.color.grey_light));

            settings_layout.setBackgroundColor(getResources().getColor(R.color.light));
            activity_layout.setBackgroundColor(getResources().getColor(R.color.light));
            instruction_layout.setBackgroundColor(getResources().getColor(R.color.light_a));
            iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
            iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on_white));
            tV_Home.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Effects.setTextColor(getResources().getColor(R.color.grey_light));
            tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey_light));
            tV_Settings.setTextColor(getResources().getColor(R.color.grey_light));
            iB_close.setImageDrawable(getResources().getDrawable(R.drawable.close_white));
        }

        iB_submitRouter.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (!ssid_field.getText().toString().equals("") || !pass_field.getText().toString().equals("")) {
                    if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                        if (Memory.theme == 0)
                            iB_submitRouter.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_on));
                        else
                            iB_submitRouter.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_on_white));
                        byte[] tx_data = new byte[33];
                        tx_data[0] = Commands.SET_WIFI_SETTENGS;
                        String ssid = ssid_field.getText().toString();
                        String pass = pass_field.getText().toString();
                        for (int i = 1; i < 16 + 1; i++) {
                            if (i < ssid.length() + 1)
                                tx_data[i] = (byte) ssid.charAt(i - 1);
                            else tx_data[i] = 0;
                        }
                        for (int i = 1; i < 16 + 1; i++) {
                            if (i < pass.length() + 1)
                                tx_data[i + 16] = (byte) pass.charAt(i - 1);
                            else tx_data[i + 16] = 0;
                        }

                        DataSender ds = new DataSender();
                        ds.execute(tx_data);

                        ssid_field.setText("");
                        pass_field.setText("");
                    } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                        if (Memory.theme == 0)
                            iB_submitRouter.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
                        else
                            iB_submitRouter.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
                    }
                }
                return false;
            }
        });

        iB_submitController.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (!ssidAP_field.getText().toString().equals("") || !passAP_field.getText().toString().equals("")) {
                    if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                        if (Memory.theme == 0)
                            iB_submitController.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_on));
                        else
                            iB_submitController.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_on_white));
                        byte[] tx_data = new byte[33];
                        tx_data[0] = Commands.SET_AP_SETTINGS;
                        String ssid = ssidAP_field.getText().toString();
                        String pass = passAP_field.getText().toString();
                        for (int i = 1; i < 16 + 1; i++) {
                            if (i < ssid.length() + 1)
                                tx_data[i] = (byte) ssid.charAt(i - 1);
                            else tx_data[i] = 0;
                        }
                        for (int i = 1; i < 16 + 1; i++) {
                            if (i < pass.length() + 1)
                                tx_data[i + 16] = (byte) pass.charAt(i - 1);
                            else tx_data[i + 16] = 0;
                        }

                        DataSender ds = new DataSender();
                        ds.execute(tx_data);

                        ssidAP_field.setText("");
                        passAP_field.setText("");
                    } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                        if (Memory.theme == 0)
                            iB_submitController.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
                        else
                            iB_submitController.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
                    }
                }
                return false;
            }
        });

        iB_submitNumleds.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (!numleds_field.getText().toString().equals("")) {
                    if(motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                        if(Memory.theme == 0)
                            iB_submitNumleds.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_on));
                        else
                            iB_submitNumleds.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_on_white));
                        byte[] tx_data = new byte[2];
                        tx_data[0] = Commands.SET_NUM_LEDS;
                        tx_data[1] = (byte) Integer.parseInt(numleds_field.getText().toString());
                        DataSender ds = new DataSender();
                        ds.execute(tx_data);
                    } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                        if(Memory.theme == 0)
                            iB_submitNumleds.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
                        else
                            iB_submitNumleds.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
                    }
                }
                return false;
            }
        });

        iB_theme.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if(motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    if(Memory.theme == 0) {
                        iB_theme.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_on_white));
                        Memory.theme = 1;
                        mainActivity.getWindow().setStatusBarColor(getResources().getColor(R.color.light));

                        tV_settings.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_numled.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_theme.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_submitNumleds.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_router.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_ssid.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_pass.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_ssidAP.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_passAP.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_submitRouter.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_controller.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_submitController.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_dark.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_dark.setText(getResources().getString(R.string.light));
                        tV_instruction.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_question.setTextColor(getResources().getColor(R.color.grey_light));

                        iB_submitRouter.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
                        iB_submitController.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
                        iB_submitNumleds.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
                        iB_instruction.setImageDrawable(getResources().getDrawable(R.drawable.about_button_white));

                        ssid_field.setBackground(getResources().getDrawable(R.drawable.net_field_white));
                        ssid_field.setTextColor(getResources().getColor(R.color.grey_light));
                        pass_field.setBackground(getResources().getDrawable(R.drawable.net_field_white));
                        pass_field.setTextColor(getResources().getColor(R.color.grey_light));
                        ssidAP_field.setBackground(getResources().getDrawable(R.drawable.net_field_white));
                        ssidAP_field.setTextColor(getResources().getColor(R.color.grey_light));
                        passAP_field.setBackground(getResources().getDrawable(R.drawable.net_field_white));
                        passAP_field.setTextColor(getResources().getColor(R.color.grey_light));
                        numleds_field.setBackground(getResources().getDrawable(R.drawable.numled_field_white));
                        numleds_field.setTextColor(getResources().getColor(R.color.grey_light));

                        settings_layout.setBackgroundColor(getResources().getColor(R.color.light));
                        activity_layout.setBackgroundColor(getResources().getColor(R.color.light));
                        instruction_layout.setBackgroundColor(getResources().getColor(R.color.light_a));
                        iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
                        iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
                        iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off_white));
                        iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on_white));
                        tV_Home.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_Effects.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey_light));
                        tV_Settings.setTextColor(getResources().getColor(R.color.grey_light));
                        iB_close.setImageDrawable(getResources().getDrawable(R.drawable.close_white));
                    } else{
                        iB_theme.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_on));
                        Memory.theme = 0;
                        mainActivity.getWindow().setStatusBarColor(getResources().getColor(R.color.dark));

                        tV_settings.setTextColor(getResources().getColor(R.color.grey));
                        tV_numled.setTextColor(getResources().getColor(R.color.grey));
                        tV_theme.setTextColor(getResources().getColor(R.color.grey));
                        tV_submitNumleds.setTextColor(getResources().getColor(R.color.grey));
                        tV_router.setTextColor(getResources().getColor(R.color.grey));
                        tV_ssid.setTextColor(getResources().getColor(R.color.grey));
                        tV_pass.setTextColor(getResources().getColor(R.color.grey));
                        tV_ssidAP.setTextColor(getResources().getColor(R.color.grey));
                        tV_passAP.setTextColor(getResources().getColor(R.color.grey));
                        tV_submitRouter.setTextColor(getResources().getColor(R.color.grey));
                        tV_controller.setTextColor(getResources().getColor(R.color.grey));
                        tV_submitController.setTextColor(getResources().getColor(R.color.grey));
                        tV_dark.setTextColor(getResources().getColor(R.color.grey));
                        tV_dark.setText(getResources().getString(R.string.dark));
                        tV_instruction.setTextColor(getResources().getColor(R.color.grey));
                        tV_question.setTextColor(getResources().getColor(R.color.grey));

                        iB_submitRouter.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
                        iB_submitController.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
                        iB_submitNumleds.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
                        iB_instruction.setImageDrawable(getResources().getDrawable(R.drawable.about_button));

                        ssid_field.setBackground(getResources().getDrawable(R.drawable.net_field));
                        ssid_field.setTextColor(getResources().getColor(R.color.grey));
                        pass_field.setBackground(getResources().getDrawable(R.drawable.net_field));
                        pass_field.setTextColor(getResources().getColor(R.color.grey));
                        ssidAP_field.setBackground(getResources().getDrawable(R.drawable.net_field));
                        ssidAP_field.setTextColor(getResources().getColor(R.color.grey));
                        passAP_field.setBackground(getResources().getDrawable(R.drawable.net_field));
                        passAP_field.setTextColor(getResources().getColor(R.color.grey));
                        numleds_field.setBackground(getResources().getDrawable(R.drawable.net_field));
                        numleds_field.setTextColor(getResources().getColor(R.color.grey));

                        settings_layout.setBackgroundColor(getResources().getColor(R.color.dark));
                        activity_layout.setBackgroundColor(getResources().getColor(R.color.dark));
                        instruction_layout.setBackgroundColor(getResources().getColor(R.color.dark_a));
                        iB_Home.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
                        iB_Effects.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
                        iB_ColorMusic.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_off));
                        iB_Settings.setImageDrawable(getResources().getDrawable(R.drawable.navigaton_on));
                        tV_Home.setTextColor(getResources().getColor(R.color.grey));
                        tV_Effects.setTextColor(getResources().getColor(R.color.grey));
                        tV_ColorMusic.setTextColor(getResources().getColor(R.color.grey));
                        tV_Settings.setTextColor(getResources().getColor(R.color.grey));
                        iB_close.setImageDrawable(getResources().getDrawable(R.drawable.close));
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    if(Memory.theme == 0){
                        iB_theme.setImageDrawable(getResources().getDrawable(R.drawable.submit_button));
                    } else{
                        iB_theme.setImageDrawable(getResources().getDrawable(R.drawable.submit_button_white));
                    }

                }

                return false;
            }
        });

        iB_instruction.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if(motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    if(Memory.theme == 0)
                        iB_instruction.setImageDrawable(getResources().getDrawable(R.drawable.about_button_on));
                    else
                        iB_instruction.setImageDrawable(getResources().getDrawable(R.drawable.about_button_on_white));
                    instruction_layout.setVisibility(View.VISIBLE);
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    if(Memory.theme == 0)
                        iB_instruction.setImageDrawable(getResources().getDrawable(R.drawable.about_button));
                    else
                        iB_instruction.setImageDrawable(getResources().getDrawable(R.drawable.about_button_white));
                }
                return false;
            }
        });

        iB_close.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                instruction_layout.setVisibility(View.INVISIBLE);
            }
        });

        return view;
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);

        if (context instanceof MainActivity) {
            this.mainActivity = (MainActivity) context;
        }
    }
}