#include "Servlet.hpp"

class UploadServlet : public Servlet {
    public:
        void doGet(Response res, Request req) override;
        void doPos(Response res, Request req) override;
}