/**
 * HW1
 * Author: Bao Tran Tran Do
 * 1/16/2022
 */

import 'dart:io';

import 'package:flutter/material.dart';
import 'package:hw1/storage/storage.dart';
import 'package:image_picker/image_picker.dart';
import 'package:provider/provider.dart';



/***
 * This class if for the todos list form where the user will fill out the form
 * with the title, description. User has the option to save or exit. Exiting
 * will not save the content. It will bring the user back to the home screen
 *
 * Source: https://api.flutter.dev/flutter/widgets/StatelessWidget-class.html
 */
class TodoFormInputsWidget extends StatelessWidget {
  ImagePicker image = ImagePicker();
  pickImage({required ImageSource source}) {}

  // Declaring the variables
  final String title;
  final String description;
  String relationType;
  String relatedTo;
  // this will be used for addingTodos and updating Todos which will
  // be handle in a different class.
  final VoidCallback savedTodo;
  final ValueChanged<String> userTitle;
  final ValueChanged<String> userDescription;
  final ValueChanged<String> userRelatedTo;
  //ValueChanged<String> userRelationType;


  // Constructor
  TodoFormInputsWidget({
    this.title = '',
    this.description = '',
    this.relationType = 'None',
    this.relatedTo = '',
    required this.userTitle,
    required this.userDescription,
    required this.savedTodo,
    required this.userRelatedTo,
    //required this.userRelationType,
    //this.dropDownMenuItem = RelationModel(),
  });

  /***
   * This is to build the form and display the form to the user with the single
   * box.
   * Building out the ordering of the widget verically
   *
   * Source: https://api.flutter.dev/flutter/widgets/Column-class.html
   * Source: https://api.flutter.dev/flutter/widgets/SingleChildScrollView-class.html
   */
  @override
  Widget build(BuildContext context) => SingleChildScrollView(
    child: Column(
      children: [

        //imageWidget(context),
        Container(height: 5),
        //build out the structure of the todo form
        relatedToFormWidget(context),
        Container(height: 5), // Adding spaces
        titleFormWidget(),
        Container(height: 5), // Create the space
        descriptionFormWidget(),
        Container(height: 5), // Create the space
        saveFormWidget(),
        exitFormWidget(context),
      ],
    ),
  );

  /***
   * Creating the title form widget for the user to enter the title
   *
   * Source: https://api.flutter.dev/flutter/material/TextField/onChanged.html
   * Source: https://api.flutter.dev/flutter/material/InputDecoration-class.html
   */
  Widget titleFormWidget() => TextFormField(
    key: Key('Title'),

    // The initial title of the task that is displayed for the user to enter
    initialValue: title,
    // This will display whatever the user type for the task
    onChanged: userTitle,
    // The max line that will be display for the user to fill out is 1
    maxLines: 1,
    style: TextStyle(height: 1),


    // Display the input text box for the title
    decoration:  InputDecoration(
      labelText: 'Title',
      border: OutlineInputBorder(),
    ),
  );

  /***
   * Creating the description form widget for the user to enter the description
   *
   * Source: https://api.flutter.dev/flutter/material/TextField/onChanged.html
   * Source: https://api.flutter.dev/flutter/material/InputDecoration-class.html
   */
  Widget descriptionFormWidget() => TextFormField(
    key: Key("Description"),
    // The initial description of the task that is displayed for the user to enter
    initialValue: description,
    // This will display whatever the user type for the task
    onChanged: userDescription,
    // The max line that will be display for the user to fill out is 1
    maxLines: 2,
    style: TextStyle(height: 2),

    // Display the input text box for the title
    decoration:  InputDecoration(
      labelText: 'Description',
      border: OutlineInputBorder(),
    ),
  );

  /***
   * The exit form widget allow the user to exit if they changed their mind
   * about creating the task card
   */
  Widget exitFormWidget(context) => Container(
    key: Key('Exit'),
    child: ElevatedButton(
      child: Text('Exit'),
      onPressed: () => Navigator.pop(context),
      style: ButtonStyle(
        backgroundColor: MaterialStateProperty.all(Colors.black),
        alignment: Alignment.center,
      ),//
      // Go back to the original screen (this case it is home)
    ),
  );


  /***
   *   Save button to save the task card
   */
  Widget saveFormWidget() => Container(
    key: Key('Save'),
    child: ElevatedButton(
      child: Text('Save'),
      onPressed: savedTodo,
      style: ButtonStyle(
        backgroundColor: MaterialStateProperty.all(Colors.green),
        alignment: Alignment.center,
      ),

    ),
  );

  /***
   * Creating the related to form widget for the user to enter the related to
   *
   * Source: https://api.flutter.dev/flutter/material/TextField/onChanged.html
   * Source: https://api.flutter.dev/flutter/material/InputDecoration-class.html
   */
  Widget relatedToFormWidget(BuildContext context) => TextFormField(
    key: Key('Related To'),
    // The initial title of the task that is displayed for the user to enter
    initialValue: relatedTo,
    // This will display whatever the user type for the task
    onChanged: userRelatedTo,
    // The max line that will be display for the user to fill out is 1
    maxLines: 1,
    style: TextStyle(height: 1, fontSize: 15),


    // Display the input text box for the title
    decoration:  InputDecoration(
      labelText: 'Related to (enter task card ID)',
      border: OutlineInputBorder(),
    ),
  );

}