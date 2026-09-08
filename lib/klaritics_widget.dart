import 'package:flutter/material.dart';

class KlariticsWidget extends StatefulWidget {
  final Widget child;
  final containerKey;
  const KlariticsWidget({Key? key, required this.child, this.containerKey}) : super(key: key);
  @override
  _KlariticsWidgetState createState() => _KlariticsWidgetState();
}

class _KlariticsWidgetState extends State<KlariticsWidget> {
  @override
  Widget build(BuildContext context) {
    return RepaintBoundary(
      key: widget.containerKey,
      child: widget.child,
    );
  }
}
