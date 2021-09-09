import React from "react";
import { shallow } from "enzyme";
import DroneListSection from "./DroneListSection";

import Accordion from "@material-ui/core/Accordion";
import AccordionSummary from "@material-ui/core/AccordionSummary";
import AccordionDetails from "@material-ui/core/AccordionDetails";
import DroneListTable from "../DroneListTable/DroneListTable";

describe("DroneListSection ", () => {
  it("should render initial layout", () => {
    const component = shallow(<DroneListSection />);
    expect(component.length).toBe(1);
  });

  it("should render Accordion", () => {
    const component = shallow(<DroneListSection />);
    expect(component.find(Accordion).length).toBe(1);
  });

  it("should render AccordionSummary", () => {
    const component = shallow(<DroneListSection />);
    expect(component.find(AccordionSummary).length).toBe(1);
  });

  it("should render AccordionDetails", () => {
    const component = shallow(<DroneListSection />);
    expect(component.find(AccordionDetails).length).toBe(1);
  });

  it("should render DroneListTable", () => {
    const component = shallow(<DroneListSection />);
    expect(component.find(DroneListTable).length).toBe(1);
  });
});
