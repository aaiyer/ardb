/*
 *Copyright (c) 2013-2013, yinqiwen <yinqiwen@gmail.com>
 *All rights reserved.
 *
 *Redistribution and use in source and binary forms, with or without
 *modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of Redis nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 *THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 *BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * backlog.hpp
 *
 *  Created on: 2013年8月22日
 *      Author: wqy
 */

#ifndef BACKLOG_HPP_
#define BACKLOG_HPP_

#include <string>
#include <vector>
#include "common.hpp"
#include "channel/all_includes.hpp"

namespace ardb
{
	struct MMapBuf
	{
			char* buf;
			uint32 size;
	};

	class ReplBacklog:public Runnable
	{
		private:
			uint32 m_backlog_size;
			uint32 m_backlog_idx;
			uint32 m_master_repl_offset;
			uint32 m_repl_backlog_histlen;
			uint32 m_repl_backlog_offset;

			typedef std::vector<MMapBuf> BacklogBufArray;
			BacklogBufArray m_backlog_bufs;
			void Run();
			void ClearMapBuf(BacklogBufArray& bufs);
			void Put(const char* buf, size_t len);
		public:
			ReplBacklog();
			int ReInit(const std::string& path, uint64 backlog_size);
			void Feed(const char* buf, size_t len);
			bool IsValidOffset(const std::string& server_key, int64 offset);
			const std::string& GetServerKey();


	};
}

#endif /* BACKLOG_HPP_ */
