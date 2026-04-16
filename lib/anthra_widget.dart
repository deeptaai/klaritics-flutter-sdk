import 'package:flutter/material.dart';

class AnthraWidget extends StatefulWidget {
  final Widget child;
  final containerKey;
  const AnthraWidget({Key? key, required this.child, this.containerKey}) : super(key: key);
  @override
  _AnthraWidgetState createState() => _AnthraWidgetState();
}

class _AnthraWidgetState extends State<AnthraWidget> {
  @override
  Widget build(BuildContext context) {
    return RepaintBoundary(
      key: widget.containerKey,
      child: widget.child,
    );
  }
}
