using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Wilfrem.HerculeMaker.MediaInterfaces;
using Wilfrem.HerculeMaker.MFWrapper;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// 空白ページのアイテム テンプレートについては、http://go.microsoft.com/fwlink/?LinkId=234238 を参照してください

namespace Wilfrem.HerculeMaker.Front
{
    /// <summary>
    /// それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// このページがフレームに表示されるときに呼び出されます。
        /// </summary>
        /// <param name="e">このページにどのように到達したかを説明するイベント データ。Parameter 
        /// プロパティは、通常、ページを構成するために使用します。</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
        }
        private async void Button_Click_1(object sender, RoutedEventArgs e)
        {
            var picker = new FileSavePicker();
            picker.SuggestedStartLocation = PickerLocationId.VideosLibrary;
            picker.FileTypeChoices.Add("WMVファイル", new List<string>(new string[1] { ".wmv" }));
            picker.SuggestedFileName = "output.wmv";
            var file = await picker.PickSaveFileAsync();
            if (file != null)
            {
                await Write(file);
                MessageDialog dialog = new MessageDialog("書き出しが終了しました");
                await dialog.ShowAsync();
            }
        }
        private async Task Write(StorageFile file)
        {
            var stream = await file.OpenAsync(FileAccessMode.ReadWrite);
            var factory = new VideoWriteServiceFactory();
            var prop = new VideoProperty();
            prop.BitRate = 800000;
            prop.Format = VideoEncoding.WindowsMediaVideo;
            prop.FPS = 25;
            prop.Height = 480;
            prop.Width = 640;
            prop.Output = stream;
            var service = factory.Create(prop);
            UInt32[] data = new UInt32[prop.Height * prop.Width];
            for (int i = 0; i < data.Length; ++i)
            {
                data[i] = 0x0000FF00;
            }
            for (int i = 0; i < 20 * prop.FPS; ++i)
            {
                service.WriteFrame(data);
            }
            service.Close();
        }
    }
}
