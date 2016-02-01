package edu.cmu.andrew.lab1_audio_image_processing;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    Button audioButton;
    Button imageButton;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);



        audioButton = (Button)findViewById(R.id.audiobutton);
        audioButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0) {
                Intent audioIntent = new Intent(MainActivity.this, AudioProcessing.class);
                startActivity(audioIntent);
            }
        });

        imageButton = (Button)findViewById(R.id.imagebutton);
        imageButton.setOnClickListener(new View.OnClickListener(){
            public void onClick(View arg0) {
                Intent imageIntent = new Intent(MainActivity.this, ImageProcessing.class);
                startActivity(imageIntent);
            }
        });


    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
