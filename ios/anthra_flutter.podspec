#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint anthra_flutter.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'anthra_flutter'
  s.version          = '2.0.0'
  s.summary          = 'Anthra Flutter plugin .'
  s.description      = <<-DESC
Flutter plugin wrapping Anthra native iOS SDKs .
                       DESC
  s.homepage         = 'https://www.apxor.com/'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Anthra' => 'dev@apxor.com' }
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*'
  s.public_header_files = 'Classes/**/*.h'
  s.dependency 'Flutter'
  s.platform = :ios, '11.0'

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }

  # ――― Project Settings ――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  
  s.requires_arc = true

  #change this before releasing ***
  s.vendored_frameworks = 'Frameworks/AnthraSDK.xcframework'
  # s.dependency 'Apxor-Core', '~> 2.10.01'
end
