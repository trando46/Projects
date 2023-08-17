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
import 'package:hw1/widget/todo_ui_shared_widget.dart';
import 'package:provider/provider.dart';

/**
 * This class will display all of the todos for shared
 *
 * Source: https://api.flutter.dev/flutter/widgets/ListView/ListView.separated.html
 */

class TodoAllListSharedWidget extends StatefulWidget {

  @override
  _TodoAllListSharedState createState() => _TodoAllListSharedState();
}

class _TodoAllListSharedState extends State<TodoAllListSharedWidget>{

  @override
  void initState()
  {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {

    final List<TodoModel> todos = Provider.of<TodosStorage>(context).firebaseTodos;


    return  ListView.separated(
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
        return TodoUISharedWidget(todo: todo);
      },
    );
  }

}