import 'package:flutter/material.dart';
import 'package:flutter_slidable/flutter_slidable.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:hw1/main.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:hw1/pages/display_todo_content_page.dart';
import 'package:hw1/storage/storage.dart';
import 'package:hw1/widget/todo_ui_homepage_layout_widget.dart';
import 'package:hw1/widget/todo_ui_individual_task_card_display_widget.dart';
import 'package:mockito/mockito.dart';
import 'package:provider/provider.dart';

class MockNavigatorObserver extends Mock implements NavigatorObserver {}

extension WithScaffold on WidgetTester {
  pumpWithScaffold(Widget widget) async =>
      pumpWidget(MaterialApp(home: Scaffold(body: widget)));
}

/***
 * Create up to three widget tests that validate that users can add, remove, or use links between tasks.
 */
void main(){

  /**
   * Removing a task card when there is already data.
   */
  testWidgets('Remove_A_Valid_Task_Card_Should_Pass', (tester) async {

    final GlobalKey<NavigatorState> nav = GlobalKey<NavigatorState>();

    final TodoModel todo1 = TodoModel(
      title: "store",
      description: "apple",
      //id: DateTime.now().toString(),
      id: 1,
      relatedTo: "",
      createdTime: DateTime.now(),
      status: 'Open',
      relationType: "None",
    );

    var storage = TodosStorage();
    storage.addTodoSQLDatabase(todo1);

    await tester.pumpWidget(
        MaterialApp(
            navigatorKey: nav,
            home: ChangeNotifierProvider<TodosStorage>(
              create: (context) => storage,
              child:  TodoUIIndividualTaskCardDisplayWidget(todo:todo1),
            )
        )
    );

    final router = MaterialPageRoute(builder: (context) => ChangeNotifierProvider<TodosStorage>(
      create: (context) => storage,
      child:  MyApp(),
    ));

    // The screen just displaying the task card with no content
    expect(find.text('store'), findsOneWidget);
    expect(find.text(todo1.description),findsNothing);

    await tester.drag(find.byType(Slidable), const Offset(50.0, 0.0));
    await tester.pump();

    expect(find.byIcon(Icons.edit),findsOneWidget);
    expect(find.text('Delete'),findsWidgets);

    // Pressed the delete button
    await tester.tap(find.byIcon(Icons.delete),warnIfMissed: false);
    nav.currentState!.push(router);
    await tester.pumpAndSettle();

    // The task card no longer present
    expect(find.text('store'), findsNothing);

  });

  testWidgets('Remove_A_Valid_Task_Card_Links_RelationShip_Should_Pass', (tester) async {

    final GlobalKey<NavigatorState> nav = GlobalKey<NavigatorState>();

    final TodoModel todo1 = TodoModel(
      title: "store",
      description: "apple",
      //id: DateTime.now().toString(),
      id: 1,
      relatedTo: "2",
      createdTime: DateTime.now(),
      status: 'Open',
      relationType: "is subtask of",
      imageFile: '',
    );

    final TodoModel todo2 = TodoModel(
      title: "Laundry",
      description: "Monday",
      //id: DateTime.now().toString(),
      id: 2,
      relatedTo: "",
      createdTime: DateTime.now(),
      status: 'Open',
      relationType: "None",
      imageFile: '',
    );


    var storage = TodosStorage();
    storage.addTodoSQLDatabase(todo1);
    storage.addTodoSQLDatabase(todo2);

    await tester.pumpWidget(
        MaterialApp(
            navigatorKey: nav,
            home: ChangeNotifierProvider<TodosStorage>(
              create: (context) => storage,
              child:  DisplayTodoContentPage(todo: todo1,),
            )
        )
    );


    // The screen just displaying the task card with no content
    expect(find.text('Title: ' + todo1.title), findsOneWidget);
    // The remove message would only display if there is a related task card
    expect(find.text('Remove the related task...'), findsOneWidget);

    await tester.tap(find.text('Remove the related task...'));
    await tester.pumpAndSettle();

    // Confirming that the message is not display anymore
    expect(find.text('Remove the related task...'), findsNothing);

  });

}