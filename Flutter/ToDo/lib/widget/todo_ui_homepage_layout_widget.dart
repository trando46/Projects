/**
 * HW1
 * Author: Bao Tran Tran Do
 * 1/16/2022
 */

import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:hw1/storage/storage.dart';
import 'package:hw1/widget/todo_ui_individual_task_card_display_widget.dart';
import 'package:provider/provider.dart';

/**
 * This class is for displaying the list of task cards in the homepage
 * This page will display all the status of the task cards minus the completed
 * ones
 *
 * Source: https://api.flutter.dev/flutter/widgets/ListView/ListView.separated.html
 */

class TodoUIHomepageLayoutWidget extends StatefulWidget {

  @override
  _TodoUIHomepageLayoutState createState() => _TodoUIHomepageLayoutState();
}

class _TodoUIHomepageLayoutState extends State<TodoUIHomepageLayoutWidget>{

  @override
  void initState()
  {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    //final provider = Provider.of<TodosStorage>(context);
    // Display all status of the task cards minus the completed
    //final todos = provider.todos;
    final List<TodoModel> todos = Provider.of<TodosStorage>(context).todos;

    // Need to take care of no todos and todos
    return todos.isEmpty ? Center(
        child: Text(
          'Need to add todos!',
          style: TextStyle(
              fontSize: 30,
              color: Colors.red
          ),
        )) : ListView.separated(
      // Special effect of scrolling and display the task cards
      itemCount: todos.length,
      scrollDirection: Axis.vertical,
      dragStartBehavior: DragStartBehavior.start,
      // Adding the spacing between each task using the container
      separatorBuilder: (context, index) => Container(
        height: 18,
        color: Colors.black12,),
      itemBuilder: (context, index) {
        final todo = todos[index];
        return TodoUIIndividualTaskCardDisplayWidget(todo:todo);
      },
    );
  }

}