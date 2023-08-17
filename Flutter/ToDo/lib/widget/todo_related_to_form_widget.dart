/**
 * HW2
 * Author: Bao Tran Tran Do
 * Note: currently on hold. Did not fully integrate
 * 1/22/2022
 */


import 'package:flutter/material.dart';
import 'package:hw1/storage/storage.dart';
import 'package:provider/provider.dart';



/***
 * This class is for the form where the user will enter the task card's id
 * to have it related to the specific relationship. Purpose of this class is
 * to allow user to add additional relations. This is on hold for now cause
 * the design is not a good idea to have a many to many relationship.
 * The displaying of the relationships can be congoluated
 * Source: https://api.flutter.dev/flutter/widgets/StatelessWidget-class.html
 */
class TodoRelatedToFormWidget extends StatelessWidget {
  String relatedTo;
  final ValueChanged<String> userRelatedTo;
  final VoidCallback savedTodo;

  TodoRelatedToFormWidget ({
    this.relatedTo ='',
    required this.userRelatedTo,
    required this.savedTodo,
});

  @override
  Widget build(BuildContext context) => SingleChildScrollView(
    child: Column(
    children: [
      //build out the structure of the related to form
      relatedToFormWidget(context),
      Container(height: 5), // Adding spaces
      saveFormWidget(),
      exitFormWidget(context),

      ],
    ),
  );

  /***
   *   Save button to save the task card
   */
  Widget saveFormWidget() => Container(
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
    // The initial title of the task that is displayed for the user to enter
    initialValue: relatedTo,
    // This will display whatever the user type for the task
    onChanged: userRelatedTo,
    // The max line that will be display for the user to fill out is 1
    maxLines: 1,
    style: TextStyle(height: 1),


    // Display the input text box for the title
    decoration:  InputDecoration(
      labelText: 'Related to (enter task card ID)',
      border: OutlineInputBorder(),
    ),
  );

  /***
   * The exit form widget allow the user to exit if they changed their mind
   * about creating the task card
   */
  Widget exitFormWidget(context) => Container(
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



}