/**********************************************************************************
 * MIT License
 * 
 * Copyright (c) 2018 Antoine Beauchamp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *********************************************************************************/

#include "TestConfiguration.h"
#include "shellanything/Configuration.h"
#include "shellanything/Item.h"
#include "shellanything/ActionExecute.h"

namespace shellanything { namespace test
{

  //--------------------------------------------------------------------------------------------------
  void TestConfiguration::SetUp()
  {
  }
  //--------------------------------------------------------------------------------------------------
  void TestConfiguration::TearDown()
  {
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestConfiguration, testDefault)
  {
    //fake the implementation
    Configuration * config = new Configuration();
    config->setFilePath("C:\\Users\\MartyMcfly\\Documents\\ShellAnything\\default.xml");
    
    // <item name="Command line from here...">
    //   <icon path="C:\Windows\System32\shell32.dll" index="3" />
    //   <validity folder="true" />
    //   <actions>
    //     <exec path="C:\windows\system32\cmd.exe" basedir="${selection.path}" />
    //   </actions>
    // </item>
    Item * item = new Item();
    item->setName("Command line from here...");
    Validator * validity = new Validator("Validity");
    validity->setMaxFiles(0); //no files accepted
    validity->setMaxDirectories(1); //a single directory is accepted
    Validator * visibility = new Validator("Visibility"); //no requirement, always visible
    ActionExecute * action = new ActionExecute();
    action->setPath("C:\\windows\\system32\\cmd.exe");
    action->setBaseDir("C:\\Users\\MartyMcfly\\AppData\\Local\\Temp");

    //link everything
    config->addChild(item);
    item->addChild(validity);
    item->addChild(visibility);
    item->addChild(action);
  }
  //--------------------------------------------------------------------------------------------------

} //namespace test
} //namespace shellanything
