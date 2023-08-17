/**
 * HW1
 * Author: Bao Tran Tran Do
 * 1/16/2022
 */

import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:hw1/widget/todo_card_structure_widget.dart';
import 'package:hw1/main.dart';
import 'package:hw1/widget/todo_has_relation_list_shared_widget.dart';
import 'package:hw1/widget/todo_inprogress_list_shared_widget.dart';
import 'package:hw1/widget/todo_open_list_widget.dart';
import 'package:hw1/widget/todo_ui_homepage_layout_widget.dart';
import 'package:hw1/widget/todo_inprogress_list_widget.dart';
import 'package:hw1/widget/todo_completed_list_widget.dart';
import 'package:hw1/widget/todos_open_list_shared_widget.dart';
import 'package:side_navigation/side_navigation.dart';
import 'package:hw1/widget/todo_has_relation_list_widget.dart';
import 'package:hw1/widget/todo_all_list_shared_widget.dart';

import '../widget/todo_completed_list_shared_widget.dart';

/***
 *
 * Want to extends the Stateful widget since the homepage needs to update the
 * list of tasks cards every time when something is added
 * Source: https://api.flutter.dev/flutter/widgets/StatefulWidget-class.html
 */
class HomePage extends StatefulWidget{

  //final camera;
  //HomePage({required this.camera});

  // https://api.flutter.dev/flutter/widgets/StatefulWidget-class.html
  @override
  _HomePageState createState() => _HomePageState();
}

/**
 * Private class for the homepage
 */
class _HomePageState extends State<HomePage> {
  // the current tab that is selected
  int selectedIndex = 0;

  Future<void> _signOut() async {
    try {
      await FirebaseAuth.instance.signOut();
    } catch (e) {
      print("[ERROR] " +e.toString());
    }
  }


  // Create the todos and the complete section at the side of the
  // navigation bar
  @override
  Widget build(BuildContext context) {
    final tabs = [
      TodoUIHomepageLayoutWidget(),
      // put the pages inside: one for todos
      TodoOpenListWidget(),
      TodoInProgressListWidget(), // one page for the inprogress todos
      TodoCompletedListWidget(), // one for the completed
      TodoHasRelationListWidget(), // one for has relation
      TodoAllListSharedWidget(),
      TodoOpenListSharedWidget(),
      TodoInProgressListSharedWidget(),
      TodoCompletedListSharedWidget(),
      TodoHasRelationListSharedWidget(),
      //Container(), // Place holder for future tabs/pages
    ];

    // Need to create Scaffold
    return Scaffold(
      appBar: AppBar(
        title: Text(MyApp.title),
        actions: [
          MaterialButton(
            child: Text(
              'Logout',
              style: TextStyle(
                  fontSize: 25.0,
                  color: Colors.white,
                  backgroundColor: Colors.grey
              ),
            ),
            onPressed: _signOut,
          ),
        ],
        // Getting the title variable from main.dart
      ),

      // Create the side naviation bar
      body: Row(
        children: [
          SideNavigationBar(
            selectedIndex: selectedIndex,

            theme: SideNavigationBarTheme(
              backgroundColor: Colors.blueGrey,
              dividerTheme: SideNavigationBarDividerTheme.standard(),
              togglerTheme: SideNavigationBarTogglerTheme.standard(),
                itemTheme: SideNavigationBarItemTheme(
                    unselectedItemColor: Colors.purple,
                    selectedItemColor: Colors.black,
                ),
            ),

            items:  [
              SideNavigationBarItem(
              icon: Icons.list_alt,
              label: 'Todos - Personal'
              ),

              SideNavigationBarItem(
                  icon: Icons.circle_outlined,
                  label: 'Open - Personal'
              ),

              SideNavigationBarItem(
              icon: Icons.run_circle,
              label: 'InProgress - Personal'
                ),

              SideNavigationBarItem(
              icon: Icons.cloud_done,
              label: 'Completed - Personal'
              ),

              SideNavigationBarItem(
                  icon: Icons.data_exploration_sharp,
                  label: 'Has Relation - Personal'
              ),

              // This is for the shared items
              SideNavigationBarItem(
                  icon: Icons.list_alt,
                  label: 'Todos - Shared'
              ),

              SideNavigationBarItem(
                  icon: Icons.circle_outlined,
                  label: 'Open - Shared'
              ),

              SideNavigationBarItem(
                  icon: Icons.run_circle,
                  label: 'InProgress - Shared'
              ),

              SideNavigationBarItem(
                  icon: Icons.cloud_done,
                  label: 'Completed - Shared'
              ),

              SideNavigationBarItem(
                  icon: Icons.data_exploration_sharp,
                  label: 'Has Relation - Shared'
              ),


              /*SideNavigationBarItem(
                  icon: Icons.camera,
                  label: 'Camera'
              ),*/
            ],

            onTap: (index) {
              setState(() {
                selectedIndex = index;
              });
            },
          ),

          // want to add the body of text
          Expanded(
            child: tabs[selectedIndex],
          ),
        ],
      ),

      //Want to add the button to add the task
      floatingActionButton: FloatingActionButton(

        // change the background color
        backgroundColor: Colors.black,
        child: Icon(Icons.add),

        // This will create the popup for the task
        // user will enter the tasks and description
        onPressed: () => showDialog(
          // This will prevent the pop-up screen to not go away
          // if click outside the box entry area.
          barrierDismissible: false,
          context: context,
          builder: (context) =>TodoCardStructureWidget(),
        ),
      ),
    );
  }
}
