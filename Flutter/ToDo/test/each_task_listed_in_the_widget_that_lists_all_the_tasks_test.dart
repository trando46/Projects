import 'package:flutter/material.dart';
import 'package:flutter_slidable/flutter_slidable.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:hw1/pages/display_todo_content_page.dart';
import 'package:hw1/pages/home_page.dart';
import 'package:hw1/pages/update_todo_page.dart';
import 'package:hw1/storage/storage.dart';
import 'package:hw1/widget/todo_completed_list_widget.dart';
import 'package:hw1/widget/todo_form_inputs_widget.dart';
import 'package:hw1/widget/todo_card_structure_widget.dart';
import 'package:hw1/widget/todo_has_relation_list_widget.dart';
import 'package:hw1/widget/todo_inprogress_list_widget.dart';
import 'package:hw1/widget/todo_open_list_widget.dart';

import 'package:hw1/main.dart';
import 'package:hw1/widget/todo_ui_homepage_layout_widget.dart';
import 'package:hw1/widget/todo_ui_individual_task_card_display_widget.dart';
import 'package:provider/provider.dart';

import 'package:mockito/mockito.dart';

class MockNavigatorObserver extends Mock implements NavigatorObserver {}

extension WithScaffold on WidgetTester {
  pumpWithScaffold(Widget widget) async =>
      pumpWidget(MaterialApp(home: Scaffold(body: widget)));
}


void main(){

  /**
   * Indicates the name of the task card
   */
  testWidgets('Indicates_The_Valid_Name_Of_The_Widget_Should_Pass', (tester) async {

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
            home: ChangeNotifierProvider<TodosStorage>(
              create: (context) => storage,
              child:  TodoUIHomepageLayoutWidget(),
            )
        )
    );

    final expectedTextFinder = find.text("store");
    expect(expectedTextFinder, findsOneWidget);

    final expectedTextFinderNothing = find.text("Yo");
    expect(expectedTextFinderNothing, findsNothing);

  });

  /**
   * has a button that when clicked tells the navigator/router to go to the widget for editing an existing task*.
   */
  testWidgets('Has_Button_For_Update_When_Click_Tells_Navigator_To_Go_To_The_Widget_For_Editing_An_Existing_Task_Should_Pass', (tester) async {

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
      child:  UpdateTodoPage(todo:todo1),
    ));

    // The screen just displaying the task card with no content
    expect(find.text('store'), findsOneWidget);
    expect(find.text(todo1.description),findsNothing);

    await tester.drag(find.byType(Slidable), const Offset(50.0, 0.0));
    await tester.pump();

    expect(find.byIcon(Icons.edit),findsOneWidget);
    expect(find.text('Edit'),findsWidgets);

    // Route to the edit page when the edit button is presssed.
    await tester.tap(find.byIcon(Icons.edit),warnIfMissed: false);
    nav.currentState!.push(router);
    await tester.pumpAndSettle();

    // Confirming that this is the edit page.
    expect(find.text('store'), findsOneWidget);
    expect(find.text(todo1.description),findsOneWidget);
    expect(find.text(todo1.relationType),findsOneWidget);
    expect(find.text(todo1.relatedTo),findsOneWidget);
    expect(find.text('Save'),findsOneWidget);
    expect(find.text('Exit'),findsOneWidget);

  });

}