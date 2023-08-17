/**
 * HW1
 * Author: Bao Tran Tran Do
 * 1/16/2022
 */

import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';
import 'package:hw1/widget/todo_ui_individual_task_card_display_widget.dart';
import 'package:provider/provider.dart';
import 'package:hw1/storage/storage.dart';

/***
 * This is the widget class for the open todos. How the cards are displayed
 * and the scrolling affect
 *
 * Source: https://api.flutter.dev/flutter/widgets/ListView/ListView.separated.html
 */
class TodoOpenListWidget extends StatelessWidget{

  @override
  Widget build(BuildContext context) {
    final provider = Provider.of<TodosStorage>(context);
    // The state to be in this class
    final todos = provider.todosIsOpen;

    // The scrolling and display affect of the task cards.
    return   ListView.separated(
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