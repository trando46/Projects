import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:hw1/main.dart';
import 'package:mockito/mockito.dart';

class MockNavigatorObserver extends Mock implements NavigatorObserver {}

extension WithScaffold on WidgetTester {
  pumpWithScaffold(Widget widget) async =>
      pumpWidget(MaterialApp(home: Scaffold(body: widget)));
}


void main(){
  /**
   * Produces a task whose title and description match the ones entered by the
   * user, where "produces" means passes the task to a provided view model or
   * to a parent widget via callback or navigation.
   */
  testWidgets('Produces_A_Task_Whose_Title_And_Description_Match_The_Ones_Entered_By_The_User_Should_Pass', (tester) async {
    String title = 'Grocery';
    String description = 'Appple';
    await tester.pumpWidget(MyApp());

    // Go to the form (The form will be the parent)
    await tester.tap(find.byIcon(Icons.add));
    await tester.pump();

    // expect to find the features of the form
    expect(find.text('Add Todo'), findsOneWidget);
    expect(find.text('Save'),findsOneWidget);
    expect(find.text('Exit'),findsOneWidget);

    // Filling out the form requires to call the Child class and once save it
    // will do a callback to the parent.
    await tester.enterText(find.byKey(Key('Title')), title);
    await tester.enterText(find.byKey(Key('Description')), description);
    await tester.tap(find.byKey(Key('Save')));
    await tester.pump();

    // exepect to only find the task card in homescreen
    expect(find.text(title), findsOneWidget);
    expect(find.text(description), findsNothing);

  });





}
