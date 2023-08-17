import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:hw1/main.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:hw1/pages/update_todo_page.dart';
import 'package:hw1/storage/storage.dart';
import 'package:provider/provider.dart';

import 'package:mockito/mockito.dart';

class MockNavigatorObserver extends Mock implements NavigatorObserver {}

extension WithScaffold on WidgetTester {
  pumpWithScaffold(Widget widget) async =>
      pumpWidget(MaterialApp(home: Scaffold(body: widget)));
}


void main(){
  /**
   * Updates the existing task instead of creating a new task.
   */
  testWidgets('Update_The_Existing_Task_Instead_Of_Creating_A_New_Task_Should_Pass', (tester) async {
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

    var update = UpdateTodoPage(todo: todo1);

    await tester.pumpWidget(
        MaterialApp(
            home: ChangeNotifierProvider<TodosStorage>(
              create: (context) => storage,
              child:  update,
            )
        )
    );

    expect( find.text("store") , findsOneWidget);
    expect(find.text("apple") , findsOneWidget);

    String title = 'Laundry';
    String description = 'Sunday';

    // updating the existing task
    await tester.enterText(find.byKey(Key('Title')), title);
    await tester.enterText(find.byKey(Key('Description')), description);
    await tester.tap(find.byKey(Key('Save')));
    await tester.pump();

    // exepect to only find the new updated task's information
    expect(find.text(title), findsOneWidget);
    expect(find.text(description), findsOneWidget);
    expect(find.text("store"),findsNothing);

  });

  /**
   * Fills out the title and description of the existing task
   */
  testWidgets('Fills_Out_The_Title_And_Description_Of_The_Existing_Task_Should_Pass', (tester) async {

    final TodoModel todo1 = TodoModel(
      title: "store",
      description: "",
      //id: DateTime.now().toString(),
      id: 1,
      relatedTo: "",
      createdTime: DateTime.now(),
      status: 'Open',
      relationType: "None",
    );

    var storage = TodosStorage();
    storage.addTodoSQLDatabase(todo1);

    var update = UpdateTodoPage(todo: todo1);

    await tester.pumpWidget(
        MaterialApp(
            home: ChangeNotifierProvider<TodosStorage>(
              create: (context) => storage,
              child:  update,
            )
        )
    );

    expect( find.text("store") , findsOneWidget);

    String title = 'Laundry';
    String description = 'Sunday';

    // updating the existing task
    await tester.enterText(find.byKey(Key('Title')), title);
    await tester.enterText(find.byKey(Key('Description')), description);
    await tester.tap(find.byKey(Key('Save')));
    await tester.pump();

    // exepect to only find the new updated task's information
    expect(find.text(title), findsOneWidget);
    expect(find.text(description), findsOneWidget);

  });

}