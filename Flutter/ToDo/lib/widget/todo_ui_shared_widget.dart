/**
 * HW1
 * Author: Bao Tran Tran Do
 * 1/16/2022
 */

import 'package:flutter/material.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:flutter_slidable/flutter_slidable.dart';
import 'package:hw1/pages/update_todo_page.dart';
import 'package:hw1/storage/storage.dart';
import 'package:provider/provider.dart';
import 'package:hw1/pages/display_todo_content_page.dart';

import '../pages/display_todo_shared_page.dart';
import '../pages/update_todo_shared_page.dart';

/***
 * This class is for how the task card are displayed on the pages and will
 * handle the routing when the user pressed the edit, remove, inprogress, and
 * done button.
 */
class TodoUISharedWidget extends StatelessWidget{

  // Declared the variables
  final TodoModel todo;

  // Constructor
  TodoUISharedWidget({
    required this.todo,
  });

  /***
   * The build function of the task and its features. If slide to the right
   * will display widgets to select between edit, inprogress, done, and remove.
   * Essentially, the status of the of the task card can be selected. All task
   * cards initially created will be mark as open
   *
   * Source: https://api.flutter.dev/flutter/widgets/ClipPath-class.html
   * Source: https://pub.dev/packages/flutter_slidable
   */
  @override
  Widget build(BuildContext context) => ClipPath(

      child: Slidable(
        //key: Key(todo.id),
        //This is for selecting the task card it will bring you the the task
        // card containing the information
        child: individualUITaskCardWidget(context),

        // The start action pane is the one at the left or the top side. This
        // will be the edit and remove functionality
        startActionPane: ActionPane(
          key:  ValueKey('start'),

          // A motion is a widget used to control how the pane animates.
          motion: const ScrollMotion(),

          // A pane can dismiss the Slidable.
          dismissible: DismissiblePane(onDismissed: () {}),

          // All actions are defined in the children parameter.
          children:  [
            // Allowing the user to edit
            SlidableAction(
              onPressed: (_) {
                editTodo(context, todo);
              },
              backgroundColor: Colors.black38,
              foregroundColor: Colors.white,
              icon: Icons.edit,
              label: 'Edit',
            ),

            // Allowing the user to delete
            SlidableAction(
              onPressed: (_) {
                deleteTodo(context, todo);
              },
              backgroundColor: Colors.red,
              foregroundColor: Colors.white,
              icon: Icons.delete,
              label: 'Delete',
            )
          ],
        ),

        // The status of the todos will be displayed on this side.
        endActionPane: ActionPane(
          // A motion is a widget used to control how the pane animates.
          motion: const ScrollMotion(),

          // A pane can dismiss the Slidable.
          dismissible: DismissiblePane(onDismissed: () {}),

          // All actions are defined in the children parameter.
          children:  [

            // Allowing the user to change the status to inprogress
            SlidableAction(
              onPressed: (_) {
                openStatusTodo(context, todo);
              },
              backgroundColor: Colors.blueGrey,
              foregroundColor: Colors.white,
              icon: Icons.circle_outlined,
              label: 'Open',
            ),

            // Allowing the user to change the status to inprogress
            SlidableAction(
              onPressed: (_) {
                inProgressStatusTodo(context, todo);
              },
              backgroundColor: Colors.blue,
              foregroundColor: Colors.white,
              icon: Icons.run_circle,
              label: 'InProgress',
            ),

            // Allowing the user to change the status to completed
            SlidableAction(
              onPressed: (_) {
                completedStatusTodo(context, todo);
              },
              backgroundColor: Colors.green,
              foregroundColor: Colors.white,
              icon: Icons.cloud_done,
              label: 'Done',
            ),
          ],

        ),
      )
  );


  /***
   * This is for the ui design of the task card. Only display the title of the
   * card
   */
  Widget individualUITaskCardWidget(BuildContext context) => GestureDetector(
    // when tap on the card it will display the todos content
    key: Key('gesture_detector'),
    onTap: () => displayTodoContent(context,todo),
    child: Container(
      color: Colors.white,
      // Padding between the interior boxes
      padding: EdgeInsets.all(15),
      child: Row(
        children: [
          // This is a place holder for when we need to add more attributes
          // to the card later
          Column(
            children: [
              // The title of the card display
              Text(
                todo.title,
                style: TextStyle(
                  fontWeight: FontWeight.bold,
                  color: Theme.of(context).primaryColorDark,
                  fontSize: 20,
                ),
              ),
            ],
          ),
        ],
      ),
    ),
  );

  /***
   * Routing this to the edit todos page to allow user to edit
   */
  void editTodo(BuildContext context, TodoModel todo) => Navigator.of(context).push(
    MaterialPageRoute(builder: (context) => UpdateTodoSharedPage(todo:todo)),
  );

  /***
   * Removing the totod from the list.
   */
  void deleteTodo(BuildContext context, TodoModel todo){
    final provider = Provider.of<TodosStorage>(context, listen: false);
    provider.removeSharedTodo(todo);
  }

  /**(
   * Routing to the page that display all of the task attributes
   */
  void displayTodoContent(BuildContext context, TodoModel todo) => Navigator.of(context).push(
    MaterialPageRoute(builder: (context) =>  DisplayTodoSharedPage(todo:todo)),
  );

  //TODO: need to fix this later
  /***
   * Changing the status to open
   */
  void openStatusTodo(BuildContext context, TodoModel todo){
    final provider = Provider.of<TodosStorage>(context, listen:false);
    provider.toggleSharedTodoIsOpenStatus(todo);
  }

  /***
   * Changing the status to inprogress
   */
  void inProgressStatusTodo(BuildContext context, TodoModel todo){
    final provider = Provider.of<TodosStorage>(context, listen:false);
    provider.toggleSharedTodoInProgressStatus(todo);
  }

  /***
   * Changing the status to completed
   */
  void completedStatusTodo(BuildContext context, TodoModel todo){
    final provider = Provider.of<TodosStorage>(context, listen:false);
    provider.toggleSharedTodoIsCompletedStatus(todo);
  }


}