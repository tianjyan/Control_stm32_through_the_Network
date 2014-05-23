using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace STM32Control
{
    public class ExceptionReportInfo
    {
        private readonly List<Exception> exceptions = new List<Exception>();

        public Exception MainException
        {
            get { return exceptions.Count > 0 ? exceptions[0] : null; }
            set
            {
                exceptions.Clear();
                exceptions.Add(value);
            }
        }

        public IList<Exception> Exceptions
        {
            get { return exceptions.AsReadOnly(); }
        }

        public void SetExceptions(IEnumerable<Exception> exceptions)
        {
            this.exceptions.Clear();
            this.exceptions.AddRange(exceptions);
        }


    }
}
