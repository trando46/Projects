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
 * Similar to the todo_completed_list_widget.dart class. This class
 * will display the inprogress task cards and the scrolling affect
 */
class TodoInProgressListWidget extends StatelessWidget{

  @override
  Widget build(BuildContext context) {
    final provider = Provider.of<TodosStorage>(context);
    // the state to be in this class
    final todos = provider.todosInProgress;

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