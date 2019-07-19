
import 'package:realm/src/dart/bindings/bindings.dart';
import 'package:realm/src/dart/bindings/types.dart' as types;
import 'package:realm/src/dart/ffi/utf8.dart';
import 'package:realm/src/dart/realmlist.dart';
import 'package:realm/src/dart/realmmodel.dart';
import 'dart:ffi';
import 'package:realm/src/dart/realmresults.dart';

part 'dog.g.dart'; 

class Dog extends RealmModel {
  String name;
  int age;
  RealmList<Dog> others;
  Dog mother;
  //FIXME: @annotate LinkingObjects(mother)
  RealmResults<Dog> litter;
}