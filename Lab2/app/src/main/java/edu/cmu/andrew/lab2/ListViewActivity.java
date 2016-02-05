package edu.cmu.andrew.lab2;

import android.app.ListActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class ListViewActivity extends ListActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String[]  myStringArray={"Blur", "Edge Detection"};

        ArrayAdapter<String> myAdapter=new ArrayAdapter<String>(
                this, android.R.layout.simple_list_item_1, myStringArray);
        ListView myList=(ListView) findViewById(R.id.listView);
        myList.setAdapter(myAdapter);
    }
}
