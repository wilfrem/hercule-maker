using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.VisualStudio.TestPlatform.UnitTestFramework;
using Wilfrem.HerculeMaker.MediaInterfaces;

namespace MediaInterfacesUnitTest
{
    [TestClass]
    public class VideoPropertyTest
    {
        VideoProperty property;
        [TestInitialize]
        public void SetUp()
        {
            property = new VideoProperty();
            property.BitRate = 12345;
            property.Format = VideoEncoding.H264;
            property.Height = 11111;
            property.Width = 12345;
            property.Output = null;
            property.FPS = 30;
        }
        [TestMethod]
        public void TestClone()
        {
            var newProp = property.Clone();
            Assert.AreEqual(property.BitRate, newProp.BitRate);
            Assert.AreEqual(property.Format, newProp.Format);
            Assert.AreEqual(property.Height, newProp.Height);
            Assert.AreEqual(property.Output, newProp.Output);
            Assert.AreEqual(property.Width, newProp.Width);
            Assert.AreEqual(property.FPS, newProp.FPS);
            Assert.AreEqual(property.GetHashCode(), newProp.GetHashCode());
        }
    }
}
