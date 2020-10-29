#include <ros/ros.h>


static sig_atomic_t volatile request_shutdown = 0; // Signal-safe flag for whether shutdown is requested

/**
 * @brief mySigIntHandler
 *        Replacement SIGINT handler
 * @param sig
 */
void mySigIntHandler(int sig)
{
  g_request_shutdown = 1;
  ROS_WARN("Shutdown request received (%d).", sig);
}

/**
 * @brief shutdownCallback
 *        Replacement "shutdown" XMLRPC callback
 * @param params
 * @param result
 */
void shutdownCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
{
  int num_params = 0;
  if (params.getType() == XmlRpc::XmlRpcValue::TypeArray)
    num_params = params.size();
  if (num_params > 1)
  {
    std::string reason = params[1];
    ROS_WARN("Shutdown request received. Reason: [%s]", reason.c_str());
    g_request_shutdown = 1; // Set flag
  }

  result = ros::xmlrpc::responseInt(1, "", 0);
}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{
  
  ros::init(argc, argv, "hover", ros::init_options::NoSigintHandler);
  ros::NodeHandle nh("~"); // Node Handler für private Parameter

  // Diagnostics
  
  // Get parameters from the parameter server and show them
  ROS_INFO("Reading parameters:");

 // Override the default ros sigint handler.
    signal(SIGINT, mySigIntHandler);

    // Override XMLRPC shutdown
    ros::XMLRPCManager::instance()->unbind("shutdown");
    ros::XMLRPCManager::instance()->bind("shutdown", shutdownCallback);

    

    while (ros::ok() && param_check_ok && !g_request_shutdown)
    {
      ros::spinOnce();   // spinOnce um callbacks zu erhalten
      loop_rate.sleep();
    }
  }

  return 0;
}
