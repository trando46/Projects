
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:hw1/pages/home_page.dart';
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
   * Testing for the homepage when only a message of 'Need to add todos!' is
   * present and no task card. No tasks card listed
   */
  testWidgets('HomePage_display_valid_message_when_there_are_no_todos_should_pass', (WidgetTester tester) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget( MyApp());

    // Verify that the message is displayed when there are no todos
    expect(find.text('Need to add todos!'), findsOneWidget);

    // Tap the '+' icon and trigger a frame.
    await tester.tap(find.byIcon(Icons.add));
    await tester.pump();

    // Verify that the text is displayed when no task cards are added
    expect(find.text('Need to add todos!'), findsOneWidget);

  });

  /**
   * has a button that when clicked tells the navigator/router to go to the widget for creating a new task*.
   */
  testWidgets('HomePage_Tap_Valid_Add_Button_Find_The_TodoCardStrcutreWidget_Should_Pass', (WidgetTester tester) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget( MyApp());

    // Tap the '+' icon and trigger a frame.
    await tester.tap(find.byIcon(Icons.add));
    await tester.pump();

    // expect to find the widget for TodoCardStructureWidget
    expect(find.byType(TodoCardStructureWidget),findsWidgets);

  });

  /**
   * Find one task card
   */
  testWidgets('Shows_One_Valid_task_Card_Widget_Should_Pass', (tester) async {

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

  });

  /**
   * Find multiple task cards
   */
  testWidgets('Shows_A_Separate_Valid_Widget_For_Each_Task_When_There_Are_Tasks_To_List_Should_Pass', (tester) async {

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

    final TodoModel todo2 = TodoModel(
      title: "School",
      description: "Need to sleep at 8",
      //id: DateTime.now().toString(),
      id: 2,
      relatedTo: "",
      createdTime: DateTime.now(),
      status: 'Open',
      relationType: "None",
    );

    final TodoModel todo3 = TodoModel(
      title: "Snowboarding",
      description: "This saturday",
      //id: DateTime.now().toString(),
      id: 3,
      relatedTo: "",
      createdTime: DateTime.now(),
      status: 'Open',
      relationType: "None",
    );

    var storage = TodosStorage();
    storage.addTodoSQLDatabase(todo1);
    storage.addTodoSQLDatabase(todo2);
    storage.addTodoSQLDatabase(todo3);

    await tester.pumpWidget(
        MaterialApp(
            home: ChangeNotifierProvider<TodosStorage>(
              create: (context) => storage,
              child:  TodoUIHomepageLayoutWidget(),
            )
        )
    );

    final expectedTextFinderStore = find.text("store");
    expect(expectedTextFinderStore, findsOneWidget);

    final expectedTextFinderSchool = find.text("School");
    expect(expectedTextFinderSchool, findsOneWidget);

    final expectedTextFinderSnowboarding = find.text("Snowboarding");
    expect(expectedTextFinderSnowboarding, findsOneWidget);

  });

  /**
   * Find only two task cards in the Open status list with the filter applied
   */
  testWidgets('Shows_Only_Two_Of_The_Open_Status_Valid_Tasks_When_A_Filter_Is_Applied_Should_Pass', (tester) async {

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

    final TodoModel todo2 = TodoModel(
      title: "School",
      description: "Need to sleep at 8",
      //id: DateTime.now().toString(),
      id: 2,
      relatedTo: "",
      createdTime: DateTime.now(),
      status: 'Open',
      relationType: "None",
    );

    final TodoModel todo3 = TodoModel(
      title: "Snowboarding",
      description: "This saturday",
      //id: DateTime.now().toString(),
      id: 3,
      relatedTo: "",
      createdTime: DateTime.now(),
      status: 'InProgress',
      relationType: "None",
    );

    var storage = TodosStorage();
    storage.addTodoSQLDatabase(todo1);
    storage.addTodoSQLDatabase(todo2);
    storage.addTodoSQLDatabase(todo3);

    await tester.pumpWidget(
        MaterialApp(
            home: ChangeNotifierProvider<TodosStorage>(
              create: (context) => storage,
              child:  TodoOpenListWidget(),
            )
        )
    );

    // Find them in the open list widget
    final expectedTextFinderStore = find.text("store");
    expect(expectedTextFinderStore, findsOneWidget);

    final expectedTextFinderSchool = find.text("School");
    expect(expectedTextFinderSchool, findsOneWidget);

    // Not displayed in the openWidget list,
    final expectedTextFinderNothingForSnowboarding = find.text("Snowboarding");
    expect(expectedTextFinderNothingForSnowboarding , findsNothing);


  });
}