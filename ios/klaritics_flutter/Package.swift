// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "klaritics_flutter",
    platforms: [
        .iOS("13.0")
    ],
    products: [
        .library(name: "klaritics-flutter", targets: ["klaritics_flutter"])
    ],
    dependencies: [
        .package(url: "https://github.com/deeptaai/klaritics-ios-sdk", from: "1.0.0")
    ],
    targets: [
        .target(
            name: "klaritics_flutter",
            dependencies: [
                .product(name: "Klaritics", package: "klaritics-ios-sdk")
            ],
            cSettings: [
                .headerSearchPath("include/klaritics_flutter")
            ]
        )
    ]
)
