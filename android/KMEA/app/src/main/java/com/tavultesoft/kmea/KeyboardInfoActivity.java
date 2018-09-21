/**
 * Copyright (C) 2017 SIL International. All rights reserved.
 */

package com.tavultesoft.kmea;

import java.io.File;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.HashMap;

import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Typeface;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.content.FileProvider;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.ImageButton;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

// Public access is necessary to avoid IllegalAccessException
public final class KeyboardInfoActivity extends AppCompatActivity {

  private static Toolbar toolbar = null;
  private static ListView listView = null;
  private static ArrayList<HashMap<String, String>> infoList = null;
  protected static Typeface titleFont = null;
  private final String titleKey = "title";
  private final String subtitleKey = "subtitle";
  private final String iconKey = "icon";

  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
    final Context context = this;

    setContentView(R.layout.activity_list_layout);
    toolbar = (Toolbar) findViewById(R.id.list_toolbar);
    setSupportActionBar(toolbar);
    getSupportActionBar().setDisplayHomeAsUpEnabled(true);
    getSupportActionBar().setDisplayShowHomeEnabled(true);
    getSupportActionBar().setDisplayShowTitleEnabled(false);

    listView = (ListView) findViewById(R.id.listView);

    final String kbID = getIntent().getStringExtra(KMManager.KMKey_KeyboardID);

    final TextView textView = (TextView) findViewById(R.id.bar_title);
    String kbName = getIntent().getStringExtra(KMManager.KMKey_KeyboardName);
    textView.setText(kbName);
    if (titleFont != null)
      textView.setTypeface(titleFont, Typeface.BOLD);

    final String kbVersion = getIntent().getStringExtra(KMManager.KMKey_KeyboardVersion);
    boolean isCustomKeyboard = getIntent().getBooleanExtra(KMManager.KMKey_CustomKeyboard, false);

    infoList = new ArrayList<HashMap<String, String>>();
    String icon = "0";
    HashMap<String, String> hashMap = new HashMap<String, String>();
    hashMap.put(titleKey, "Keyboard version");
    hashMap.put(subtitleKey, kbVersion);
    hashMap.put(iconKey, icon);
    infoList.add(hashMap);

    final String customHelpLink = getIntent().getStringExtra(KMManager.KMKey_CustomHelpLink);
    if (!isCustomKeyboard || customHelpLink != null) {
      icon = String.valueOf(R.drawable.ic_arrow_forward);
      hashMap = new HashMap<String, String>();
      hashMap.put(titleKey, "Help link");
      hashMap.put(subtitleKey, "");
      hashMap.put(iconKey, icon);
      infoList.add(hashMap);
    }

    String[] from = new String[]{titleKey, subtitleKey, iconKey};
    int[] to = new int[]{R.id.text1, R.id.text2, R.id.image1};
    ListAdapter adapter = new SimpleAdapter(context, infoList, R.layout.list_row_layout2, from, to);
    listView.setAdapter(adapter);
    listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {

      @Override
      public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        if (position == 1) {
          Intent i = new Intent(Intent.ACTION_VIEW);

          if (customHelpLink != null) {
            if (customHelpLink.endsWith("welcome.htm")) {
              File customHelp = new File(new File(customHelpLink).getAbsolutePath());
              i.setFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
              // Starting with Android N, you can't pass file:// to intents, so we use FileProvider
              try {
                Uri contentUri = FileProvider.getUriForFile(
                  context, getApplication().getPackageName() + ".fileProvider", customHelp);
                i.setDataAndType(contentUri, "text/html");
              } catch (Exception e) {
                Log.e("KeyboardInfoActivity", "Failed to access " + customHelp.toString());
              }
            }
            else {
              i.setData(Uri.parse(customHelpLink));
            }
            startActivity(i);
          } else {
            String helpUrlStr = String.format("http://help.keyman.com/keyboard/%s/%s/", kbID, kbVersion);
            i.setData(Uri.parse(helpUrlStr));
            startActivity(i);
          }
        }
      }


    });


  }

  @Override
  public boolean onSupportNavigateUp() {
    super.onBackPressed();
    return true;
  }

}
