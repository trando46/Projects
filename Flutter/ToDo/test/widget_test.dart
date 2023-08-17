// This is a basic Flutter widget test.
//
// To perform an interaction with a widget in your test, use the WidgetTester
// utility in the flutter_test package. For example, you can send tap and scroll
// gestures. You can also use WidgetTester to find child widgets in the widget
// tree, read text, and verify that the values of widget properties are correct.



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

void main() {
  /*testWidgets('Counter increments smoke test', (WidgetTester tester) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget(const MyApp());

    // Verify that our counter starts at 0.
    expect(find.text('0'), findsOneWidget);
    expect(find.text('1'), findsNothing);

    // Tap the '+' icon and trigger a frame.
    await tester.tap(find.byIcon(Icons.add));
    await tester.pump();

    // Verify that our counter has incremented.
    expect(find.text('0'), findsNothing);
    expect(find.text('1'), findsOneWidget);
  });*/

  /*testWidgets(
      "commonTextFormField default if no parameter passed",
          (WidgetTester tester) async {
        final childWidget = HomePage();
        await tester.pumpWidget(
          MaterialApp(
            home: Material(child: childWidget),
          ),
        );
        await tester.pump();

        // Verify that our counter starts at 0.
        expect(find.text('Need to add todos!'), findsOneWidget);
        //expect(find.text('1'), findsNothing);

        // Tap the '+' icon and trigger a frame.
        await tester.tap(find.byIcon(Icons.add));
        await tester.pump();

        // Verify that our counter has incremented.
        expect(find.text('0'), findsNothing);
        expect(find.text(''), findsOneWidget);

    
  });*/


  /**
   * Testing for the empty open status list
   */
  testWidgets('Open_list_widget_Valid_display_nothing_when_there_are_no_todos_should_pass', (WidgetTester tester) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget(MultiProvider(
      providers: [
        Provider<TodosStorage>(
          create: (context) => TodosStorage(),
          //builder: (context) => TodoOpenListWidget(),
        ),
        Provider<TodoOpenListWidget>(
          create: (context) => TodoOpenListWidget(),
        ),

      ],
      child: Builder(
        builder: (_) => MyApp(),
      ),
    ),);

    // Tap the 'cloud_done' icon and trigger a frame.
    await tester.tap(find.byIcon(Icons.circle_outlined));
    await tester.pump();

    // Expect
    expect(find.text(''), findsNothing);

  });

  /**
   * Testing for the empty completed status list
   */
  testWidgets('Completed_list_widget_Valid_display_nothing_when_there_are_no_todos_should_pass', (WidgetTester tester) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget(MultiProvider(
      providers: [
        Provider<TodosStorage>(
          create: (context) => TodosStorage(),
          //builder: (context) => TodoOpenListWidget(),
        ),
        Provider<TodoCompletedListWidget>(
          create: (context) => TodoCompletedListWidget(),
        ),

      ],
      child: Builder(
        builder: (_) => MyApp(),
      ),
    ),);

    // Tap the 'cloud_done' icon and trigger a frame.
    await tester.tap(find.byIcon(Icons.cloud_done));
    await tester.pump();

    // Expect
    expect(find.text(''), findsNothing);

  });


  /**
   * Testing for the empty inprogress status list
   */
  testWidgets('InProgress_list_widget_Valid_display_nothing_when_there_are_no_todos_should_pass', (WidgetTester tester) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget(MultiProvider(
      providers: [
        Provider<TodosStorage>(
          create: (context) => TodosStorage(),
          //builder: (context) => TodoOpenListWidget(),
        ),
        Provider<TodoInProgressListWidget>(
          create: (context) => TodoInProgressListWidget(),
        ),

      ],
      child: Builder(
        builder: (_) => MyApp(),
      ),
    ),);

    // Tap the 'run_circle' icon and trigger a frame.
    await tester.tap(find.byIcon(Icons.run_circle));
    await tester.pump();

    // Expect
    expect(find.text(''), findsNothing);

  });

  /**
   * Testing for the empty hasrelation status list
   */
  testWidgets('HasRelation_list_widget_Valid_display_nothing_when_there_are_no_todos_should_pass', (WidgetTester tester) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget(MultiProvider(
      providers: [
        Provider<TodosStorage>(
          create: (context) => TodosStorage(),
          //builder: (context) => TodoOpenListWidget(),
        ),
        Provider<TodoHasRelationListWidget>(
          create: (context) => TodoHasRelationListWidget(),
        ),

      ],
      child: Builder(
        builder: (_) => MyApp(),
      ),
    ),);

    // Tap the 'run_circle' icon and trigger a frame.
    await tester.tap(find.byIcon(Icons.data_exploration_sharp));
    await tester.pump();

    // Expect
    expect(find.text(''), findsNothing);

  });






  /**
   * Testing for the TodoFormInputsWidgets bring test up to 100%
   */
  testWidgets('TodoFormInputsWidget_Widgets_Valid_Should_Pass', (WidgetTester tester) async {
    final mockObserver = MockNavigatorObserver();
    final title = 'grocery';
    final description = 'milk';
    final relatedTo = 'None';

    final TodoModel todo = TodoModel(
      title: title,
      description: description,
      //id: DateTime.now().toString(),
      id: 1,
      relatedTo: "",
      createdTime: DateTime.now(),
      status: 'Open',
      relationType: relatedTo,
    );

    TodosStorage().addTodoSQLDatabase(todo);

    final form = TodoFormInputsWidget(
      userTitle: (String userTitle) {userTitle=title;},
      userDescription: (String userDescription) {userDescription =description;},
      savedTodo: () {},
      userRelatedTo: (String userRelatedTo) {userRelatedTo=relatedTo;},
    );

    await tester.pumpWithScaffold(form);

    final textArea = find.byType(TextFormField);
    expect(textArea, findsWidgets);

    final containers = find.byType(Container);
    expect(containers, findsWidgets);

    final submitButton = find.byType(ElevatedButton);
    expect(submitButton, findsWidgets);

    await tester.tap(find.byType(Navigator));
    await tester.pumpAndSettle();
  });


}

