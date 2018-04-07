using Newtonsoft.Json;
using System.Collections.Generic;
using System.IO;

namespace JSONParser.Model
{
    public class Parser
    {
        public Parser() { }
        public List<User> Parse(string path)
        {
            return JsonConvert.DeserializeObject<List<User>>(File.ReadAllText(path));
        }

    }
}
