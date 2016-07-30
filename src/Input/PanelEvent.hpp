#pragma once

#ifndef JUBEAT_ONLINE_PANEL_EVENT_HPP
#define JUBEAT_ONLINE_PANEL_EVENT_HPP

namespace jubeat_online {
	namespace input {
		class PanelEvent {
		private:


		public:
			enum Type : bool {
				PUSH = true,
				RELEASE = false
			};

			PanelEvent() {}
			virtual ~PanelEvent() {}

			virtual void process(const unsigned char panel_no, const Type type) = 0;

		};
	}
}

#endif
